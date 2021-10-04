#include <entity.hpp>
#include <utils.hpp>
#include <vector>

std::vector<entity*> entity_list;
void entity::setloc(double x,double y){
    this->x=x;
    this->y=y;
}

void entity_tick(){
    for(int i=0;i<entity_list.size();++i){
        entity_list[i]->tick();
    }

}

void entity_rentick(){
    for(int i=0;entity_list.size()>i;++i){
        entity_list[i]->rentick();
    }


}
