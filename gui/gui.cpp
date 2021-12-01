#include "gui/gui.hpp"
#include "gui/title.hpp"
#include "gui/ingame.hpp"

#include <iostream>
guielement* (*gamegui[])[]={
    &title,&ingame
};

extern bool render_gamerunning;
extern bool gamerunning;
bool guiidxchanged=false;


void togglegame(){
   render_gamerunning=!render_gamerunning;
    guiidxchanged=true;
}


int currentguiidx=0;//title screen

void changegui(int in){
    currentguiidx=in;
}
int i;
void guitick(){
     i=0;
    while((*gamegui[currentguiidx])[i]!=0&&!guiidxchanged){

        (*gamegui[currentguiidx])[i]->tick();
        ++i;
    }
    guiidxchanged=false;


}
