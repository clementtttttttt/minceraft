#include "aabb.hpp"
#include <blocks.hpp>
#include <entity.hpp>
#include <entity/player.hpp>
#include <iostream>
#include <utils.hpp>
#include <world.hpp>
#include <audio.hpp>
#include <api.hpp>
extern void *tex;
rect player_tex[]{{0, 16, 16, 96 * 2},   {16, 16, 16, 96 * 2},
                      {32, 16, 16, 96 * 2},  {0},
                      {16, 16, -16, 96 * 2}, {32, 16, -16, 96 * 2}};
extern unsigned long long tickselapsed;
rect center;
extern std::vector<aabb> block_coll;

void player::tick() {

  double ymorg = ymomentum;
  double xmorg = xmomentum;
  double tmpx = xmomentum;
  double tmpy = ymomentum;
  unsigned long long sz = block_coll.size();

  for (unsigned long long i = 0; i < sz; ++i) {
    tmpy = block_coll[i].clipYCollide(this->entity_aabb, tmpy);
    tmpx = block_coll[i].clipXCollide(this->entity_aabb, tmpx);

  }

 // tmpx = aabb(-20, -20, 20, 1000).clipXCollide(this->entity_aabb, tmpx);

  if (xmorg != tmpx) {
    xmomentum = 0;
  }
  if (ymorg != tmpy) {
    ymomentum = 0;
  }

  for (unsigned long long i = 0; i < sz; ++i) {


    if(block_coll[i].isintersect_aabb(this->entity_aabb)){

            this->y = block_coll[i].maxy + 0.2;
    }

  }



  this->onground = ymorg != tmpy && ymorg < 0;

  this->y += ymomentum;

  this->x += xmomentum;

    this->entity_aabb = aabb(this->x, this->y, this->x + 0.9, this->y + 1.8);


    std::vector<std::vector<block>> *world_ref = truncf(this->x)>=-0.99?&world:&negworld;

  xmomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  ymomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  if (ymomentum > -blockreg[(*world_ref)[abs(this->x)][this->y].type].cgrav) {
    ymomentum -= 0.07;
  }
}
player::player(double x, double y) {
  this->x = x;
  this->y = y;
}

int player::gettype() { return player_t; }
int anim_count = 0;
extern int scrnw, scrnh;
void player::rentick() {
  double blockcorner_x = (entity_list[0]->getpos().x) - (scrnw / 2 / 64);
  double blockcorner_y = (entity_list[0]->getpos().y) - (scrnh / 2 / 64) + 1;
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
    if (tickselapsed % (long long)(12 - abs(xmomentum * 30) + 2) == 0) {
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 1){
            playnoise(12,1,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 2){
            playnoise(12,40 ,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 3){
            playnoise(12,75,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 4){
            playnoise(12,30,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 5){
            playnoise(12,100,0.7);
        }
      if (anim_count > 3) {
        anim_count = 1;
      }
      if (anim_count + 1 != 3)
        ++anim_count;
      else
        anim_count = 1;
    }
  } else if (this->xmomentum < -0.009) {
    this->direction=0;
    if (tickselapsed % (long long)(12 - abs(xmomentum * 30) + 2) == 0) {
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 1){
            playnoise(12,1,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 2){
            playnoise(12,40,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 3){
            playnoise(12,75,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 4){
            playnoise(12,30,0.7);
        }
        if((*world_ref)[truncf(entity_list[0]->getpos().x)][truncf(entity_list[0]->getpos().y)-1].type == 5){
            playnoise(12,100,0.7);
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
