#include <utils.hpp>
#include <iostream>
#include "gui/elements/button.hpp"
#include <unistd.h>

SDL_Texture *idle,*hover,*clicked;
bool button_init=false;
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
    SDL_Rect dest={(int)this->x-3-8,(int)this->y,(int)(this->szx+strlen(this->text)*4+2+16),(int)this->szy+8};
    if(mx>dest.x&&mx<dest.x+dest.w&&my>dest.y&&my<dest.y+dest.h){
        if(mbuttons&SDL_BUTTON_LMASK){
            blit(clicked,&src,&dest);
            this->activate=true;
        }
        else   blit(hover,&src,&dest);


    }
    else blit(idle,&src,&dest);
    if(this->activate==true&&!(mbuttons&SDL_BUTTON_LMASK)){
        if(mx>dest.x&&mx<dest.x+dest.w&&my>dest.y&&my<dest.y+dest.h){
            this->handler();
            usleep(1);

        }
                this->activate=false;


    }
        SDL_SetTextureColorMod(font,0,0,0);

    prints(this->x+(this->szx/2-strlen(this->text)*8)-3-4,this->y+10,0.6,0.6,"%s\n",this->text,255);

}
