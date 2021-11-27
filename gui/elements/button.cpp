#include <utils.hpp>
#include <iostream>
#include "gui/elements/button.hpp"

SDL_Texture *idle,*hover,*clicked;
bool button_init=false;
bool activate=false;
button::button(const char* text,u32 x,u32 y,u32 szx,u32 szy,void(*in)()){
    this->x=x;
    this->y=y;
    this->text=text;
    this->szx=szx;
    this->szy=szy;
    this->handler=in;

}
void button::tick(){
    if(!button_init){
        button_init=true;
        idle=loadtex("guitex/button_notclicked.png");
        hover=loadtex("guitex/button_hover.png");
        clicked=loadtex("guitex/button_clicked.png");
    }
    int mx, my;
    SDL_Rect src={0,0,95,36};
    unsigned int mbuttons = SDL_GetMouseState(&mx, &my);
    SDL_Rect dest={this->x-3-8,this->y,this->szx+strlen(this->text)*4+2+16,this->szy+8};
    if(mx>dest.x&&mx<dest.x+dest.w&&my>dest.y&&my<dest.y+dest.h){
        if(mbuttons&SDL_BUTTON_LMASK){
            blit(clicked,&src,&dest);
            activate=true;
        }
        else   blit(hover,&src,&dest);


    }
    else blit(idle,&src,&dest);
    if(activate==true&&!(mbuttons&SDL_BUTTON_LMASK)){
        this->handler();
        activate=false;
    }
    prints(this->x+(26),this->y+10,0.6,0.6,"%s\n",this->text);

}
