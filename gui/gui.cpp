#include "gui/gui.hpp"
#include "gui/title.hpp"
#include "gui/ingame.hpp"

#include <iostream>
guielement* (*gamegui[])[]={
    &title,&ingame
};

extern bool render_gamerunning;
extern bool gamerunning;


void togglegame(){
   render_gamerunning=!render_gamerunning;

}


int currentguiidx=0;//title screen

void changegui(int in){
    currentguiidx=in;
}

void guitick(){
    int i=0;
    while((*gamegui[currentguiidx])[i]!=0){
        (*gamegui[currentguiidx])[i]->tick();
        ++i;
    }

}
