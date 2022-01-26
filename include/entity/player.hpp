#include <entity.hpp>
#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
class player: public entity{
    public:

        void tick();
        void rentick();
        player(double x,double y);
        int gettype();
};


#endif // PLAYER_HPP_INCLUDED
