#include "aabb.hpp"
#include <blocks.hpp>
#include <entity.hpp>
#include <entity/player.hpp>
#include <iostream>
#include <utils.hpp>
#include <world.hpp>
extern SDL_Texture *tex;
extern app mainapp;
SDL_Rect player_tex[]{{0, 16, 16, 96 * 2},   {16, 16, 16, 96 * 2},
                      {32, 16, 16, 96 * 2},  {0},
                      {16, 16, -16, 96 * 2}, {32, 16, -16, 96 * 2}};
extern unsigned long long tickselapsed;
SDL_Rect center;
extern std::vector<aabb> block_coll;

void player::tick() {

  double ymorg = ymomentum;
  double xmorg = xmomentum;
  double tmpx = xmomentum;
  double tmpy = ymomentum;
  unsigned long long sz = block_coll.size();

  for (unsigned long long i = 0; i < sz; ++i) {
    tmpy = block_coll[i].clipYCollide(this->entity_aabb, tmpy);
  }

  for (unsigned long long i = 0; i < sz; ++i) {
    tmpx = block_coll[i].clipXCollide(this->entity_aabb, tmpx);
  }
 // tmpx = aabb(-20, -20, 20, 1000).clipXCollide(this->entity_aabb, tmpx);

  if (xmorg != tmpx) {
    xmomentum = 0;
  }
  if (ymorg != tmpy) {
    ymomentum = 0;
  }

  this->onground = ymorg != tmpy && ymorg < 0;

  this->y += ymomentum;

  this->x += xmomentum;
    std::vector<std::vector<block>> *world_ref = this->x?&world:&negworld;

  xmomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  ymomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  this->entity_aabb = aabb(this->x, this->y, this->x + 0.9, this->y + 1.8);
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
  SDL_GetRendererOutputSize(mainapp.renderer, &w, &h);
  //            putblocc((*world_ref2)[absposx][posy].type,x * 64 - (scrnoffx * 64), scrnh - (y * 64 + scrnoffy * 64),64);
  center.x = (entity_list[0]->getpos().x - blockcorner_x) * 64 ;
  center.y = (entity_list[0]->getpos().y - blockcorner_y) * 64 + (scrnh%128);
  //center.y=scrnh/2-(scrnh/2%64);
  if (this->xmomentum > 0.009) {
    if (tickselapsed % (long long)(10 - abs(xmomentum * 30) + 2) == 0) {
      if (anim_count > 3) {
        anim_count = 1;
      }
      if (anim_count + 1 != 3)
        ++anim_count;
      else
        anim_count = 1;
    }
  } else if (this->xmomentum < -0.009) {
    if (tickselapsed % (long long)(10 - abs(xmomentum * 30) + 2) == 0) {
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
  blit(tex, &player_tex[anim_count], &center);
}
