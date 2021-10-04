#ifndef WORLDRENDR_HPP_INCLUDED
#define WORLDRENDR_HPP_INCLUDED
#include <vector>
#include "entity.hpp"
void worldrendr();
void worldtick();
extern std::vector<entity*> entity_list;

#endif // WORLDRENDR_HPP_INCLUDED
