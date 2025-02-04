#include <string>
#include <vector>
#include  <aabb.hpp>
#include <iostream>
#include <types.hpp>
#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED



class entity{
    public:
        entity(double x,double y);

        void setloc(double x,double y);
        virtual void tick();
        virtual void rentick(){}
        vec2 spawnblockpos; //the block that spawns this entity
        virtual int gettype(){return 0;}
        void setmomentum(double xmomentum,double ymomentum){
            if(xmomentum){
            this->xmomentum=xmomentum;
            }
            if(ymomentum){
            this->ymomentum=ymomentum;
            }
        }
        int get_health(){
            return this->health;
        }
         vec2 getpos(){
                 vec2 v;

            v.x=this->x;
            v.y=this->y;
            return v;
        }
        vec2 get_momentum(){
                 vec2 v;

            v.x=this->xmomentum;
            v.y=this->ymomentum;
            return v;
        }

        bool get_onground(){
            return this->onground;

        }
        int direction=0;//0=left,1=right
        aabb entity_aabb={0,0,0,0};


    protected:
        bool onground;

        double x=0,y=0,xmomentum=0,ymomentum=0;
        int health=100;
        long long inventory[8][4];
};
void entity_rentick();

void entity_tick();

enum type{
    nil,ENTITY_PLAYER,ENTITY_PIG
};
extern std::vector<entity*> entity_list;

#endif // ENTITY_HPP_INCLUDED
