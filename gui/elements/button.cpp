#include <iostream>
#include "gui/elements/button.hpp"
#include <api.hpp>

bool button_init=false;
button::button(const char* text,u32 x,u32 y,u32 szx,u32 szy,void(*in)()){
    this->x=x;
    this->y=y;
    this->text=text;
    this->szx=szx;
    this->szy=szy;
    this->handler=in;

}
void* idle,*hover,*clicked;
void button::tick(){
    if(!button_init){
        idle=sysspec_loadtex("guitex/button_notclicked.png");
        hover=sysspec_loadtex("guitex/button_hover.png");
        clicked=sysspec_loadtex("guitex/button_clicked.png");
        button_init=true;
    }
    int mx, my;
    rect src={0,0,95,36};
    unsigned int mbuttons = sysspec_getmousepos(&mx, &my);
    rect dest={(int)this->x-3-8,(int)this->y,(int)(this->szx+strlen(this->text)*4+2+16),(int)this->szy+8};
    if(mx>dest.x&&mx<dest.x+dest.w&&my>dest.y&&my<dest.y+dest.h){
        if(mbuttons&sysspec_mleft){
            sysspec_putimg(clicked,&src,&dest);
            this->activate=true;
        }
        else   sysspec_putimg(hover,&src,&dest);


    }
    else sysspec_putimg(idle,&src,&dest);
    if(this->activate==true&&!(mbuttons&sysspec_mleft)){
        if(mx>dest.x&&mx<dest.x+dest.w&&my>dest.y&&my<dest.y+dest.h){
            this->handler();

        }
                this->activate=false;


    }
    extern void* font;
        sysspec_setcolourmod(font,0,0,0);

    sysspec_prints(this->x+(this->szx/2-strlen(this->text)*8)-3-4,this->y+10,0.6,0.6,this->text);

}
