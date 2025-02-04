#include "gui/elements/label.hpp"
#include <api.hpp>
void label::setText(const char *text){
    strcpy(this->text,text);
}
label::label(const char* text,u32 x,u32 y){
    this->x=x;
    this->y=y;
    strcpy(this->text,text);
    this->xsc=1;
    this->ysc=1;
    this->r=0;
    this->g=0;
    this->b=0;

}
label::label(const char* text,u32 x,u32 y,float xsc,float ysc,u8 r,u8 g,u8 b){
    this->x=x;
    this->y=y;
    strcpy(this->text,text);
    this->xsc=xsc;
    this->ysc=ysc;
    this->r=r;
    this->g=g;
    this->b=b;

}
void label::tick(){
extern void* font;
    sysspec_setcolourmod(font,this->r,this->g,this->b);
    sysspec_prints(this->x,this->y,this->xsc,this->ysc,this->text);

}
