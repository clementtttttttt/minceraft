#include <blocks.hpp>
#include <chrono>
#include <entity.hpp>
#include <iostream>
#include <tick.hpp>
#include <types.hpp>
#include <utils.hpp>
#include <world.hpp>
#include <gui/gui.hpp>
#include <cmath>
#include <gui/guielement.hpp>
#include <api.hpp>
extern guielement* ingame[];
extern int currentguiidx;
extern unsigned char *keystate;
extern unsigned long long tickselapsed;
char mousebuttonstate[2]; // 0 is mleftbutton, 1 is mrightbutton
char frameskip_toggle = 1;
bool render_gamerunning=false;
bool gamerunning=false;

  int mx, my,bmx,bmy;


void ren_tick() {
  timer_start if (frameskip_toggle) {
    sysspec_clearscrn();

    if(render_gamerunning){

        worldrendr();
        entity_rentick();
    }
    guitick();

    sysspec_updatescrn();

  }
  ++tickselapsed;
  timer_stop if ((timer_val / 1000) <= 6) {
    double d = (6 - (double)(timer_val / 1000));
    sysspec_delay(d);
    frameskip_toggle = 1;
  }
  else if ((timer_val / 1000) <= 34) frameskip_toggle = !frameskip_toggle;

}
bool canbreak = true;
double prevy;

int current_invbar_idx=1;

bool escpressed=0;

void input_tick() {
  if(render_gamerunning){
  extern u8 upmousebutton;
  extern std::vector<std::vector<block>> world,negworld;
  vec2 pos = entity_list[0]->getpos();
    if(gamerunning){
        std::vector<std::vector<block>> *world_ref = pos.x>=-0.99?&world:&negworld;

  if (keystate[sysspec_key_r]) {

    entity_list[0]->setmomentum(
        keystate[sysspec_key_run]
            ? 0.3 * blockreg[(*world_ref)[abs(pos.x)][pos.y].type].cfriction
            : 0.2 * blockreg[(*world_ref)[abs(pos.x)][pos.y].type].cfriction,
        0);
  }
  if (keystate[sysspec_key_l]) {
    entity_list[0]->setmomentum(
        keystate[sysspec_key_run]
            ? -0.3 * blockreg[(*world_ref)[abs(pos.x)][pos.y].type].cfriction
            : -0.2 * blockreg[(*world_ref)[abs(pos.x)][pos.y].type].cfriction,
        0);
  }

  if (keystate[sysspec_key_jump]) {
    if (entity_list[0]->get_onground() ||
        (blockreg[(*world_ref)[abs(pos.x)][pos.y].type].bitfield & 1 << 5))
      entity_list[0]->setmomentum(
          0, 0.8 * (blockreg[(*world_ref)[abs(pos.x)][pos.y].type].cfriction * 0.8));
  }
  }
  if(keystate[sysspec_key_pause]&&!escpressed){
    escpressed=true;
    if(currentguiidx!=2){
        changegui(2);
    }
    else changegui(1);
    gamerunning=!gamerunning;
  }
  if(!keystate[sysspec_key_pause])
    escpressed=false;
  for(int i=0;i<8;++i){
    if(keystate[sysspec_key_invbar0+i]){
        current_invbar_idx=i;
    }
  }

  prevy = entity_list[0]->get_momentum().y;

  unsigned int mbuttons = sysspec_getmousepos(&mx, &my);
  extern int scrnw, scrnh;
  double scrnoffx =
      entity_list[0]->getpos().x - (long long)(entity_list[0]->getpos().x);
  double scrnoffy =
      std::round(entity_list[0]->getpos().y) - entity_list[0]->getpos().y;
  double blockcorner_x =
      (entity_list[0]->getpos().x) - (scrnw / 2 / 64) + scrnoffx;
  double blockcorner_y =
      (entity_list[0]->getpos().y) - (scrnh / 2 / 64)  + scrnoffy;
  int modmx=(mx+(scrnoffx*64));
  int modmy=(my+(scrnoffy*64));

  if(gamerunning){
        std::vector<std::vector<block>> *world_ref = floor(blockcorner_x + lround(((double)mx-fmod(modmx,64.0)) / 64.0) - ((scrnw % 64) / 64))>=-0.99?&world:&negworld;

    if ((mbuttons & sysspec_mleft) && canbreak == true && (*world_ref)[abs(blockcorner_x + lround(((double)mx-fmod(modmx,64.0)) / 64.0) - ((scrnw % 64) / 64))][(blockcorner_y + (scrnh - my) / 64 - (scrnh % 64) / 64)].type != 5) {
        (*world_ref)[abs(blockcorner_x + lround(((double)mx-fmod(modmx,64.0)) / 64.0) - ((scrnw % 64) / 64))][(blockcorner_y + (scrnh - (my-modmy%64)) / 64 - (scrnh % 64) / 64)].type = 0;
    }
  }
  bmx=((mx) / 64 - (scrnw % 64) / 64);
  bmy=((my) / 64 - (scrnh % 64) / 64);

  }
}
int world_time = 8000; // 23:59==23999
bool wt_toggle = false;
extern int quitthread;
void *game_thread(void *unused) {
  while (1) {
    if(quitthread){
        break;
    }
    keystate = (unsigned char *)sysspec_getkeystate();
    if(gamerunning){

        if ((world_time < 24000)) {
            if (wt_toggle == true)
                world_time += 1;
        } else
            world_time = 0;
        worldtick();
        entity_tick();
        wt_toggle = !wt_toggle;

    }
    input_tick();

    sysspec_delay(25);
  }
  return 0;
}
