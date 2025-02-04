#include <entity.hpp>
#include <utils.hpp>
#include <vector>
#include <blocks.hpp>
#include "world.hpp"
std::vector<entity*> entity_list;
extern std::vector<aabb> block_coll;
int anim_count;
void entity::setloc(double x,double y){
    this->x=x;
    this->y=y;
}


void entity::tick(){

  double ymorg = ymomentum;
  double xmorg = xmomentum;
  double tmpx = xmomentum;
  double tmpy = ymomentum;
  unsigned long long sz = block_coll.size();

  for (unsigned long long i = 0; i < sz; ++i) {
    tmpy = block_coll[i].clipYCollide(this->entity_aabb, tmpy);
    tmpx = block_coll[i].clipXCollide(this->entity_aabb, tmpx);

  }

  for(entity* i: entity_list){
        tmpy = i->entity_aabb.clipYCollide(this->entity_aabb, tmpy);
        tmpx = i->entity_aabb.clipXCollide(this->entity_aabb, tmpx);

  }

 // tmpx = aabb(-20, -20, 20, 1000).clipXCollide(this->entity_aabb, tmpx);

  if (xmorg != tmpx) {
    xmomentum = tmpx;
  }
  if (ymorg != tmpy) {
    ymomentum = tmpy;
  }




  this->onground = ymorg != tmpy && ymorg < 0;

  this->y += ymomentum;

  this->x += xmomentum;

    this->entity_aabb.move(xmomentum,ymomentum); //= aabb(this->x, this->y, this->x + 0.9, this->y + 1.8);


    std::vector<std::vector<block>> *world_ref = truncf(this->x)>=-0.99?&world:&negworld;

  xmomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  ymomentum *= blockreg[(*world_ref)[abs(this->x)][this->y].type].cfriction;

  if (ymomentum > -blockreg[(*world_ref)[abs(this->x)][this->y].type].cgrav) {
    ymomentum -= 0.07;
  }
}


void entity_tick(){
    for(int i=0;i<entity_list.size();++i){
        entity_list[i]->tick();
    }

}

entity::entity(double x, double y){
    this->x=x;
    this->y=y;

}
void entity_rentick(){
    for(int i=0;entity_list.size()>i;++i){
        entity_list[i]->rentick();
    }


}
