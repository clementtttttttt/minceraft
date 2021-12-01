#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <gui/elements/image.hpp>
#include <utils.hpp>
#include <iostream>

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos+((screensz_y-640)/640)*640

image invbar("guitex/ingame_invbar.png",screensz_x/2-274,60,137*4,18*4,137*4,18*4,255);


void hm(){
    std::cout << "TEST"<<std::endl;
}


guielement* ingame[]={
    &invbar,(guielement*) 0

};
