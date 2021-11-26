#include <utils.hpp>
#include "gui/elements/label.hpp"

label::label(const char* text,u32 x,u32 y){
    this->x=x;
    this->y=y;
    this->text=text;

}
void label::tick(){
    prints(this->x,this->y,"%s\n",this->text);

}
