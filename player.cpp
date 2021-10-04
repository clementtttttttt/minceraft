#include <entity/player.hpp>
#include <entity.hpp>
#include <iostream>
#include <utils.hpp>
#include "aabb.hpp"
extern SDL_Texture* tex;
extern app mainapp;
SDL_Rect player_tex[]{
    {0,16,16,96*2},
    {16,16,16,96*2},
    {32,16,16,96*2},
    {0},
    {16,16,-16,96*2},
    {32,16,-16,96*2}
};
extern unsigned long long tickselapsed;
SDL_Rect center;
extern std::vector<aabb> block_coll;

void player::tick(){
    double ymorg=ymomentum;
    double xmorg=xmomentum;
    double tmpx=xmomentum;
    double tmpy=ymomentum;
    unsigned long long sz=block_coll.size();


    for(unsigned long long i=0;i<sz;++i){
        tmpy=block_coll[i].clipYCollide(this->entity_aabb,tmpy);

    }

    for(unsigned long long i=0;i<sz;++i){
        tmpx=block_coll[i].clipXCollide(this->entity_aabb,tmpx);

    }
    tmpx=aabb(-20,-20,20,1000).clipXCollide(this->entity_aabb,tmpx);

    if(xmorg!=tmpx){
        xmomentum=0;
    }
    if(ymorg!=tmpy){
        ymomentum=0;
    }



    this->y+=ymomentum;

    this->x+=xmomentum;
    xmomentum*=0.85;

    ymomentum*=0.85;

    this->entity_aabb=aabb(this->x,this->y,this->x+0.9,this->y+1.8);
    if(ymomentum>-9.8){
        ymomentum-=0.07;
    }
}
player::player(double x,double y){
    this->x=x;
    this->y=y;

}

int player::gettype(){
    return player_t;
}
int anim_count=0;
extern int scrnw,scrnh;
void player::rentick(){
    double blockcorner_x=(entity_list[0]->getpos().x)-(scrnw/2/64);
    double blockcorner_y=(entity_list[0]->getpos().y)-(scrnh/2/64)+1;;
    center.w=player_tex[0].w*4;
    center.h=player_tex[0].h*4;
    int w,h;
    SDL_GetRendererOutputSize(mainapp.renderer,&w,&h);
    center.x=(entity_list[0]->getpos().x-blockcorner_x)*64;
    center.y=(entity_list[0]->getpos().y-blockcorner_y)*64+(scrnh%64);
    if(this->xmomentum>0.09){
        if(tickselapsed%(long long)(8-abs(xmomentum*10))==0){
            if(anim_count>3){
                anim_count=1;
            }
            if(anim_count+1!=3)
            ++anim_count;
            else anim_count=1;
        }
    }
    else if(this->xmomentum<-0.09){
        if(tickselapsed%(long long)(8-abs(xmomentum*10))==0){
            if(anim_count<3){
                anim_count=3;
            }
            if(anim_count+1!=6)
            ++anim_count;
            else anim_count=4;
        }
    }
    else anim_count=0;
    blit(tex,&player_tex[anim_count],&center);


}
