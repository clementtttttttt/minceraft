#include <utils.hpp>
#include <gui/label.hpp>

label::label(const char* text){
    this->text=text;

}
void label::tick(){
    prints(this->x,this->y,this->text);

}
