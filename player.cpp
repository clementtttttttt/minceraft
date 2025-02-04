#include "aabb.hpp"
#include <blocks.hpp>
#include <entity.hpp>
#include <entity/player.hpp>
#include <iostream>
#include <utils.hpp>
#include <world.hpp>
#include <audio.hpp>
#include <math.h>
#include <api.hpp>
extern void *tex;
rect player_tex[]{{0, 16, 16, 96 * 2},   {16, 16, 16, 96 * 2},
                      {32, 16, 16, 96 * 2},  {0},
                      {16, 16, -16, 96 * 2}, {32, 16, -16, 96 * 2}};
extern unsigned long long tickselapsed;
static rect center;
extern std::vector<aabb> block_coll;

void player::tick(){
entity::tick();

}
player::player(double x, double y) :
entity(x, y,0.9,1.8)
{
}

int player::gettype() { return ENTITY_PLAYER; }
static int anim_count = 0;
extern int scrnw, scrnh;
void player::rentick() {
  double blockcorner_x = (entity_list[0]->getpos().x) - (scrnw / 2 / 64);
  double blockcorner_y = (entity_list[0]->getpos().y) - (scrnh / 2 / 64)+1;
  ;
  center.w = player_tex[0].w * 4;
  center.h = player_tex[0].h * 4;
  int w, h;
  sysspec_getscreensz(&w,&h);
  //            putblocc((*world_ref2)[absposx][posy].type,x * 64 - (scrnoffx * 64), scrnh - (y * 64 + scrnoffy * 64),64);
  center.x = (entity_list[0]->getpos().x - blockcorner_x) * 64 ;
  center.y = (entity_list[0]->getpos().y - blockcorner_y) * 64 + (scrnh%128);
  //center.y=scrnh/2-(scrnh/2%64);
    std::vector<std::vector<block>> *world_ref = truncf(this->x)>=-0.99?&world:&negworld;

  if (this->xmomentum > 0.009) {
    this->direction=1;
    if ((tickselapsed % (long long)(20 - abs(xmomentum * 30) + 2)) == 0) {
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 1){
            playnoise(12,1,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 2){
            playnoise(12,40,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 3){
            playnoise(12,75,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 4){
            playnoise(12,20,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 5){
            playnoise(12,140,0.7);
        }
      if (anim_count > 3) {
        anim_count = 0;
      }
      if (anim_count + 1 != 3)
        ++anim_count;
      else
        anim_count = 1;
    }
  } else if (this->xmomentum < -0.009) {
    this->direction=0;
    if ((tickselapsed % (long long)(20 - abs(xmomentum * 30) + 2)) == 0) {
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 1){
            playnoise(12,1,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 2){
            playnoise(12,40,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 3){
            playnoise(12,75,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 4){
            playnoise(12,20,0.7);
        }
        if((*world_ref)[abs(truncf(entity_list[0]->getpos().x))][truncf(entity_list[0]->getpos().y)-1].type == 5){
            playnoise(12,140,0.7);
        }
      if (anim_count < 3) {
        anim_count = 3;
      }
      if (anim_count + 1 != 6)
        ++anim_count;
      else
        anim_count = 4;
    }
  } else
    anim_count = 0;
  sysspec_putimg(tex, &player_tex[anim_count], &center);
}
