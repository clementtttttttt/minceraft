#ifndef WORLDRENDR_HPP_INCLUDED
#define WORLDRENDR_HPP_INCLUDED
#include <vector>
#include "entity.hpp"
#include <blocks.hpp>
void worldrendr();
void worldtick();
extern std::vector<entity*> entity_list;

extern std::vector<std::vector<block>> world,negworld;

block getBlock(double x, double y);

#endif // WORLDRENDR_HPP_INCLUDED
