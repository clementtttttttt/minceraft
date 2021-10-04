#ifndef RAYCASTSHADE_HPP_INCLUDED
#define RAYCASTSHADE_HPP_INCLUDED
#include"entity.hpp"
int compute_ray(double orgx,double orgy,double direction,int light);//returns true when the ray hits smth , false when ray goes OOB without hitting shit, LIGHT SRC ONLY
void compute_shade(long long bx,long long by,struct vec2 p_pos);
#endif // RAYCASTSHADE_HPP_INCLUDED
