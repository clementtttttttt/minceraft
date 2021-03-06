#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <gui/elements/image.hpp>
#include <utils.hpp>
#include <iostream>
#include <gui/gui.hpp>
#include <fileformat.hpp>
#include <tinyfiledialogs.h>
#include <string>
extern const char* gitversion;

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos*screensz_y/640
char const* pattern[]={"*.minceworld"};

void playbuttonhandler(){
    char* path=tinyfd_openFileDialog("Select your minceraft world","",1,pattern,"minceraft world",0);
    if(path==0){

        tinyfd_messageBox("Warning!","Making a new world!","ok","warning",1);
    }
    else{
        int err=load_world(path);
        switch(err){
            case 1:
                tinyfd_messageBox("CRIKEY!","Invalid magic! Making a new world!","ok","warning",1);
            break;
            case 2:
                tinyfd_messageBox("CRIKEY!","File doesn't exist / accecss denied! Making a new world!","ok","warning",1);
            break;
        }
    }
        changegui(1);

    togglegame();


}

image title_minceraft("guitex/title_minceraft.png",screensz_x/2-(319*8/4/2*screensz_x/1024),calctoppos(40),319*8/4*screensz_x/1024,56*8/4*screensz_y/640,319,56,255);
button play_button("Play",calccentrepos(4),calctoppos(200),32*4,64,playbuttonhandler);
image background("guitex/title_background.png",0,0,screensz_x,screensz_y,128,72,255);
char gitrevstr[77]="git rev ";
label commitver(strcat(gitrevstr,gitversion),5,screensz_y-24,0.25,0.25,255,255,255);

guielement* title[]={
    &background,&title_minceraft,&play_button,&commitver,(guielement*) 0

};
