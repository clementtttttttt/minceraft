#include <tick.hpp>
#include <utils.hpp>
#include <entity.hpp>
#include <SDL.h>
#include <world.hpp>
#include <iostream>
#include <chrono>
#include <blocks.hpp>
#include <types.hpp>
extern app mainapp;
extern unsigned char* keystate;
extern unsigned long long tickselapsed;
char mousebuttonstate[2];//0 is mleftbutton, 1 is mrightbutton
char frameskip_toggle=1;
void ren_tick(){
    timer_start
    if(frameskip_toggle){
            SDL_RenderClear(mainapp.renderer);

        worldrendr();
        entity_rentick();
                SDL_RenderPresent(mainapp.renderer);

    }
            ++tickselapsed;
    timer_stop
    if((timer_val/1000)<=17){
        double d=(17-(double)(timer_val/1000));
        SDL_Delay(d);
        frameskip_toggle=1;
    }
    else if((timer_val/1000)<=34) frameskip_toggle=!frameskip_toggle;


}
double prevy;
void input_tick(){
    if(keystate[SDL_SCANCODE_D]){

        entity_list[0]->setmomentum(keystate[SDL_SCANCODE_LSHIFT]?0.3:0.2,0);
    }
    if(keystate[SDL_SCANCODE_A]){
        entity_list[0]->setmomentum(keystate[SDL_SCANCODE_LSHIFT]?-0.3:-0.2,0);
    }

    if(keystate[SDL_SCANCODE_SPACE]){
        if(entity_list[0]->getpos().y==prevy)
        entity_list[0]->setmomentum(0,0.6);
    }
    prevy=entity_list[0]->getpos().y;
    int mx,my;
    unsigned int mbuttons=SDL_GetMouseState(&mx,&my);
    extern std::vector<std::vector<block>> world;
     extern    int scrnw,scrnh;
    double  scrnoffx=entity_list[0]->getpos().x-(long long) (entity_list[0]->getpos().x);
    double scrnoffy=round(entity_list[0]->getpos().y)-entity_list[0]->getpos().y;
    double blockcorner_x=(entity_list[0]->getpos().x)-(scrnw/2/64)+scrnoffx;
    double blockcorner_y=(entity_list[0]->getpos().y)-(scrnh/2/64)+1+scrnoffy;

    if(mbuttons&SDL_BUTTON_LMASK){
        world[(blockcorner_x+(mx)/64-(scrnw%64)/64)][(blockcorner_y+(scrnh-my)/64-(scrnh%64)/64)].type=0;
    }

}
int world_time=8000; //23:59==23999
bool wt_toggle=false;
void* game_thread(void* unused){
    while(1){
        if((world_time<24000)){
            if(wt_toggle==true)
                world_time+=1;
        }
        else world_time=0;
        keystate=(unsigned char*)SDL_GetKeyboardState(NULL);
        worldtick();
        input_tick();

        entity_tick();
        SDL_Delay(25);
        wt_toggle=!wt_toggle;
    }
    return 0;
}
