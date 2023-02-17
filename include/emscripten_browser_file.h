#ifndef EMSCRIPTEN_UPLOAD_FILE_H_INCLUDED
#define EMSCRIPTEN_UPLOAD_FILE_H_INCLUDED

#include <string>
#include <emscripten.h>

namespace emscripten_browser_file {

using upload_handler = void(*)(std::string const&, std::string const&, std::string_view buffer, void*);

EM_JS(void, upload, (char const *accept_types, upload_handler callback, void *callback_data = nullptr), {
  /// Prompt the browser to open the file selector dialogue, and pass the file to the given handler
  /// Accept-types are in the format ".png,.jpeg,.jpg" as per https://developer.mozilla.org/en-US/docs/Web/HTML/Attributes/accept
  /// Upload handler callback signature is:
  ///   void my_handler(std::string const filename, std::string const &mime_type, std::string_view buffer, void *callback_data = nullptr);
  globalThis.open_file = function(e) {
    const file_reader = new FileReader();
    file_reader.onload = (event) => {
      const uint8Arr = new Uint8Array(event.target.result);
      const num_bytes = uint8Arr.length * uint8Arr.BYTES_PER_ELEMENT;
      const data_ptr = Module._malloc(num_bytes);
      const data_on_heap = new Uint8Array(Module.HEAPU8.buffer, data_ptr, num_bytes);
      data_on_heap.set(uint8Arr);
      var callback_data = callback_data || 0;
      const res = Module.ccall('load_file_return', 'number', ['string', 'string', 'number', 'number', 'number', 'number'], [event.target.filename, event.target.mime_type, data_on_heap.byteOffset, uint8Arr.length, callback, callback_data]);
      Module._free(data_ptr);
    };
    file_reader.filename = e.target.files[0].name;
    file_reader.mime_type = e.target.files[0].type;
    file_reader.readAsArrayBuffer(e.target.files[0]);
  };

  var file_selector = document.createElement('input');
  file_selector.setAttribute('type', 'file');
  file_selector.setAttribute('onchange', 'open_file(event)');
  file_selector.setAttribute('accept', UTF8ToString(accept_types));
  file_selector.click();
});

void upload(std::string const &accept_types, upload_handler callback, void *callback_data = nullptr) {
  /// C++ wrapper for javascript upload call
  upload(accept_types.c_str(), callback, callback_data);
}

EM_JS(void, download, (char const *filename, char const *mime_type, void const *buffer, size_t buffer_size), {
  /// Offer a buffer in memory as a file to download, specifying download filename and mime type
  var a = document.createElement('a');
  a.download = UTF8ToString(filename);
  a.href = URL.createObjectURL(new Blob([new Uint8Array(Module.HEAPU8.buffer, buffer, buffer_size)], {type: UTF8ToString(mime_type)}));
  a.click();
});

void download(std::string const &filename, std::string const &mime_type, std::string_view buffer) {
  /// C++ wrapper for javascript download call, accepting a string_view
  download(filename.c_str(), mime_type.c_str(), buffer.data(), buffer.size());
}

namespace {

extern "C" {

EMSCRIPTEN_KEEPALIVE int load_file_return(char const *filename, char const *mime_type, char *buffer, size_t buffer_size, upload_handler callback, void *callback_data) {
  /// Load a file - this function is called from javascript when the file upload is activated
  callback(filename, mime_type, {buffer, buffer_size}, callback_data);
  return 1;
}

}

}

}

#endif // EMSCRIPTEN_UPLOAD_FILE_H_INCLUDED
