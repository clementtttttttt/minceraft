#include <string>
#include <vector>
#include  <aabb.hpp>
#include <iostream>
#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

struct vec2{
    double x,y;
};

class entity{
    public:
        void setloc(double x,double y);
        virtual void tick(){}
        virtual void rentick(){}
        virtual int gettype(){return 0;}
        void setmomentum(double xmomentum,double ymomentum){
            if(xmomentum){
            this->xmomentum=xmomentum;
            }
            if(ymomentum){
            this->ymomentum=ymomentum;
            }
        }
        struct vec2 getpos(){
                struct vec2 v;

            v.x=this->x;
            v.y=this->y;
            return v;
        }
        aabb entity_aabb={0,0,0,0};

    protected:
        double x=0,y=0,xmomentum=0,ymomentum=0;
        int health=100;
};
void entity_rentick();

void entity_tick();

enum type{
    nil,player_t
};
extern std::vector<entity*> entity_list;

#endif // ENTITY_HPP_INCLUDED
