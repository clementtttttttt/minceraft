#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <gui/elements/image.hpp>
#include <utils.hpp>
#include <iostream>
#include <gui/gui.hpp>
#include <fileformat.hpp>
#include <tinyfiledialogs.h>
#include <string>
#include <cstring>

#ifdef EMCXX
#include <emscripten.h>
#include "emscripten_browser_file.h"

#endif // EMCXX
extern const char* gitversion;

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos*screensz_y/640
char const* pattern[]={"*.minceworld"};
int err;
int loaded = 0;
void em_load_wrd(
    std::string const &filename,  // the filename of the file the user selected
    std::string const &mime_type, // the MIME type of the file the user selected, for example "image/png"
    std::string_view buffer,      // the file's content is exposed in this string_view - access the data with buffer.data() and size with buffer.size().
    void *callback_data = nullptr // optional callback data - identical to whatever you passed to handle_upload_file()
){
    err=load_world(buffer);
    loaded=1;
}
void playbuttonhandler(){
    #ifdef EMCXX
    loaded=0;
    emscripten_browser_file::upload(".minceworld,",em_load_wrd);
    while(loaded == 0){
        emscripten_sleep(10);
        std::cout << loaded << std::endl;
    }
    switch(err){
            case 1:
                std::cout << "WARNING!" << " Invalid magic! Making a new world!" << std::endl;
            break;
            case 2:
                std::cout << "File doesn't exist / accecss denied! Making a new world!" << std::endl;

            break;
        }
    #else
    char* path=tinyfd_openFileDialog("Select your minceraft world","",1,pattern,"minceraft world",0);

    if(path==0){

        tinyfd_messageBox("Warning!","Making a new world!","ok","warning",1);
    }
    else{
        int err=load_world(path);
        switch(err){
            case 1:
                tinyfd_messageBox("WARNING!","Invalid magic! Making a new world!","ok","warning",1);
            break;
            case 2:
                tinyfd_messageBox("WARNING!","File doesn't exist / accecss denied! Making a new world!","ok","warning",1);
            break;
        }
    }
    #endif

        changegui(1);

    togglegame();


}

image title_minceraft("guitex/title_minceraft.png",screensz_x/2-(319*8/4/2*screensz_x/1024),calctoppos(40),319*8/4*screensz_x/1024,56*8/4*screensz_y/640,319,56,255);
button play_button("Play",calccentrepos(4),calctoppos(200),32*4,64,playbuttonhandler);
image background("guitex/title_background.png",0,0,screensz_x,screensz_y,128,72,255);
char gitrevstr[77]="git rev ";
label commitver(std::strcat(gitrevstr,gitversion),5,screensz_y-24,0.25,0.25,255,255,255);

guielement* title[]={
    &background,&title_minceraft,&play_button,&commitver,(guielement*) 0

};
