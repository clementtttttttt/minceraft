#include <blocks.hpp>
#include <entity.hpp>
#include <entity/player.hpp>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <tick.hpp>
#include <types.hpp>
#include <fileformat.hpp>
#include <api.hpp>
#include <audio.hpp>
#ifdef EMCXX
#include <emscripten.h>
#endif
int quitthread=0;
pthread_t gamethread, audiothread;
extern std::vector<entity *> entity_list;
unsigned char *keystate;
unsigned long long tickselapsed = 0;

u8 upmousebutton;

extern int mx,my;
  bool init_m = false;

void em_tick(){
    while (sysspec_poll()) {
      upmousebutton = 0;
      sysspec_checkquit();

    }
      if (init_m == false) {
        init_m = true;

    pthread_create(&gamethread, NULL, game_thread, NULL);
        pthread_create(&audiothread, NULL, audio_thread, NULL);
      }
    ren_tick();

}
int main(){

  sysspec_init();

  rect block_clips[] = {{96, 16, 16, 16}, {240, 240, 16, 16}};
  register_block(0, 0, 0, 0, (rect){0, 0, 16, 16}, "Air", 0.85, 9.8, 1);
  register_block(1, 0, 1, 0, (rect){16, 0, 16, 16}, "Grass", 0.85, 9.8, 1);
  register_block(2, 0, 1, 0, (rect){32, 0, 16, 16}, "Dirt", 0.85, 9.8, 1);
  register_block(3, 0, 1, 0, (rect){48, 0, 16, 16}, "Stone", 0.85, 9.8, 1);
  register_block(4, 0, 1, 0, (rect){64, 0, 16, 16}, "Sand", 0.85, 9.8, 1);
  register_block(5, 0, 0, 1, (rect){80, 0, 16, 16}, "Water", 0.5, 1, 1.33333333);
  entity_list.push_back(new player(180, 60));

  #ifdef EMCXX
    emscripten_set_main_loop(em_tick,60,1);

  #else// EMCXX
  while (1) {

    em_tick();
  }
  #endif
  extern pthread_t rtxthreado;
quit:
  quitthread=1;
  pthread_join(gamethread,0);
  pthread_join(audiothread,0);
  pthread_join(rtxthreado,0);

  exit(0);
}
