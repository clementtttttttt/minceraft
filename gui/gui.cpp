#include "gui/gui.hpp"
#include "gui/title.hpp"
#include <iostream>
guielement* (*gamegui[])[]={
    &title
};

extern bool gamerunning;

void togglegame(){
    gamerunning=!gamerunning;
}

int currentguiidx=0;//title screen

void guitick(){
    int i=0;
    while((*gamegui[currentguiidx])[i]!=0){
        (*gamegui[currentguiidx])[i]->tick();
        ++i;
    }

}
