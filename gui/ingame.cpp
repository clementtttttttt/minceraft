#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <utils.hpp>
#include <iostream>

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos+((screensz_y-640)/640)*640

void hm(){
    std::cout << "TEST"<<std::endl;
}


guielement* ingame[]={
    (guielement*) 0

};
