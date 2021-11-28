#include <utils.hpp>
#include "gui/elements/label.hpp"

label::label(const char* text,u32 x,u32 y){
    this->x=x;
    this->y=y;
    this->text=text;
    this->xsc=1;
    this->ysc=1;

}
label::label(const char* text,u32 x,u32 y,float xsc,float ysc){
    this->x=x;
    this->y=y;
    this->text=text;
    this->xsc=xsc;
    this->ysc=ysc;

}
void label::tick(){
    prints(this->x,this->y,this->xsc,this->ysc,"%s\n",this->text);

}
