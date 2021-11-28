#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <gui/elements/image.hpp>
#include <utils.hpp>
#include <iostream>
#include <gui/gui.hpp>
#include <tinyfiledialogs.h>
#include <string>
extern const char* gitversion;

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos*(screensz_y/640)
char const* pattern[]={"*.minceworld"};

void playbuttonhandler(){
    char* path=tinyfd_openFileDialog("Select your minceraft world","",1,pattern,"minceraft world",0);
    if(path==0){
        tinyfd_messageBox("Warning","You will need to specify the location in which your world would be saved with the save world option in the pause menu, or else it will be saved as lastworld.minceworld!","ok","warning",1);
    }
    changegui(1);
    togglegame();

}

label title_minceraft("Minceraft",screensz_x/2-(144)-(18),calctoppos(60));
button play_button("Play",calccentrepos(4),calctoppos(200),32*4,64,playbuttonhandler);
image background("guitex/title_background.png",0,0,screensz_x,screensz_y,128,72);
char gitrevstr[77]="git rev ";
label commitver(strcat(gitrevstr,gitversion),5,screensz_y-24,0.25,0.25);

guielement* title[]={
    &background,&title_minceraft,&play_button,&commitver,(guielement*) 0

};
