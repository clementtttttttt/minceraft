#include <SDL.h>
#include <blocks.hpp>
#include <chrono>
#include <entity.hpp>
#include <iostream>
#include <tick.hpp>
#include <types.hpp>
#include <utils.hpp>
#include <world.hpp>
#include <gui/gui.hpp>
extern app mainapp;
extern unsigned char *keystate;
extern unsigned long long tickselapsed;
char mousebuttonstate[2]; // 0 is mleftbutton, 1 is mrightbutton
char frameskip_toggle = 1;
bool render_gamerunning=false;
bool gamerunning=false;

  int mx, my,bmx,bmy;


void ren_tick() {
  timer_start if (frameskip_toggle) {
    SDL_RenderClear(mainapp.renderer);

    if(render_gamerunning){
        worldrendr();
        entity_rentick();
    }
    guitick();

    SDL_RenderPresent(mainapp.renderer);
    if(render_gamerunning)         gamerunning=true;

  }
  ++tickselapsed;
  timer_stop if ((timer_val / 1000) <= 17) {
    double d = (17 - (double)(timer_val / 1000));
    SDL_Delay(d);
    frameskip_toggle = 1;
  }
  else if ((timer_val / 1000) <= 34) frameskip_toggle = !frameskip_toggle;

}
bool canbreak = true;
double prevy;
extern SDL_Event e;

int current_invbar_idx=1;

void input_tick() {
  if(render_gamerunning){
  extern u8 upmousebutton;
  extern std::vector<std::vector<block>> world;
  vec2 pos = entity_list[0]->getpos();

  if (keystate[SDL_SCANCODE_D]) {

    entity_list[0]->setmomentum(
        keystate[SDL_SCANCODE_LSHIFT]
            ? 0.3 * blockreg[world[pos.x][pos.y].type].cfriction
            : 0.2 * blockreg[world[pos.x][pos.y].type].cfriction,
        0);
  }
  if (keystate[SDL_SCANCODE_A]) {
    entity_list[0]->setmomentum(
        keystate[SDL_SCANCODE_LSHIFT]
            ? -0.3 * blockreg[world[pos.x][pos.y].type].cfriction
            : -0.2 * blockreg[world[pos.x][pos.y].type].cfriction,
        0);
  }

  if (keystate[SDL_SCANCODE_SPACE]) {
    if (entity_list[0]->getonground() ||
        (blockreg[world[pos.x][pos.y].type].bitfield & 1 << 5))
      entity_list[0]->setmomentum(
          0, 0.8 * (blockreg[world[pos.x][pos.y].type].cfriction * 0.8));
  }
  for(int i=0;i<8;++i){
    if(keystate[SDL_SCANCODE_1+i]){
        current_invbar_idx=i;
    }
  }

  prevy = entity_list[0]->getmomentum().y;

  unsigned int mbuttons = SDL_GetMouseState(&mx, &my);
  extern int scrnw, scrnh;
  double scrnoffx =
      entity_list[0]->getpos().x - (long long)(entity_list[0]->getpos().x);
  double scrnoffy =
      round(entity_list[0]->getpos().y) - entity_list[0]->getpos().y;
  double blockcorner_x =
      (entity_list[0]->getpos().x) - (scrnw / 2 / 64) + scrnoffx;
  double blockcorner_y =
      (entity_list[0]->getpos().y) - (scrnh / 2 / 64) + 1 + scrnoffy;
  if ((mbuttons & SDL_BUTTON_LMASK) && canbreak == true && world[(blockcorner_x + (mx) / 64 - (scrnw % 64) / 64)] [(blockcorner_y + (scrnh - my) / 64 - (scrnh % 64) / 64)].type != 5) {
    world[(blockcorner_x + (mx) / 64 - (scrnw % 64) / 64)][(blockcorner_y + (scrnh - my) / 64 - (scrnh % 64) / 64)].type = 0;
  }
  bmx=((mx) / 64 - (scrnw % 64) / 64);
  bmy=((my) / 64 - (scrnh % 64) / 64);

  }
}
int world_time = 8000; // 23:59==23999
bool wt_toggle = false;
void *game_thread(void *unused) {
  while (1) {

    if ((world_time < 24000)) {
      if (wt_toggle == true)
        world_time += 1;
    } else
      world_time = 0;
    keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
    if(gamerunning){
        worldtick();
        entity_tick();
    }
    input_tick();

    SDL_Delay(25);
    wt_toggle = !wt_toggle;
  }
  return 0;
}
