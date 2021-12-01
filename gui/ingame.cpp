#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <gui/elements/image.hpp>
#include <gui/elements/customtick.hpp>
#include <utils.hpp>
#include <iostream>

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos+((screensz_y-640)/640)*640

extern guielement* ingame[];

void invbarachangehan(){
    int mx,my;
    SDL_GetMouseState(&mx, &my);
    if(mx>ingame[1]->x&&my>ingame[1]->y){
        if(mx<(ingame[1]->x+137*4)&&my<ingame[1]->y+18*4){
            ingame[1]->transparency=128;
        }
        else ingame[1]->transparency=255;

    }
    else ingame[1]->transparency=255;

}

image invbar("guitex/ingame_invbar.png",screensz_x/2-274,calctoppos(500),137*4,18*4,137,18,255);
customtick invbaralphachange(invbarachangehan);



guielement* ingame[]={
    &invbaralphachange,&invbar,(guielement*) 0

};
