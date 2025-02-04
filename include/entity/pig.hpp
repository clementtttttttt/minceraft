#ifndef ENTITY_PIG_H
#define ENTITY_PIG_H
#include "entity.hpp"

#include <queue>
class pig : public entity
{
    public:
        pig();
        virtual ~pig();
        void rentick();
        pig(double x,double y) ;
        void tick()override;
        int gettype();
    protected:
bool is_valid_walking_target();
std::queue<vec2> pathing_queue;
vec2 old_target_pos;
vec2 walk_target;

    private:
};

#endif // ENTITY_PIG_H
