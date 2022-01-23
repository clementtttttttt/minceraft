#include <gui/gpause.hpp>
#include <gui/gui.hpp>
#include <gui/elements/image.hpp>
#include <gui/elements/button.hpp>
#include <utils.hpp>
#define calctoppos(pos) pos*screensz_y/640

extern bool gamerunning;

void resume(){
    changegui(1);
    gamerunning=true;

}
void save(){
    changegui(1);

    gamerunning=true;

}


image gpause_background("guitex/gpause_background.png",0,0,screensz_x,screensz_y,128,72,255);
button gpause_resume_button("Resume",screensz_x/2-96,calctoppos(50),192,64,resume);
button gpause_save_button("Save & Quit",screensz_x/2-96-8,calctoppos(50+64+16),192,64,save);


guielement* gpause[]={
    &gpause_background,&gpause_resume_button,&gpause_save_button,(guielement*)0
};
