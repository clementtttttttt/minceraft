#ifndef AABB_HPP
#define AABB_HPP

#include <iostream>
class aabb
{
    public:
        aabb(double minx,double miny,double maxx,double maxy);
        double clipXCollide(aabb c, double xa) ;
        double clipYCollide(aabb c, double xa) ;
        bool isintersect(double px,double py){
            aabb a=(*this);
            return px>=a.minx&&px<=a.maxx&&py>=a.miny&&py<=a.maxy;
        }
        bool isintersect_aabb(aabb c){
            return c.minx > this->minx &&
                   c.minx < this->maxx &&
                   c.miny > this->miny &&
                   c.miny < this->maxy ||

                   c.maxx > this->minx &&
                   c.maxx < this->maxx &&
                   c.miny > this->miny &&
                   c.miny < this->maxy;
        }
        void move(double xa, double d);


        double minx,miny,maxx,maxy;
};

#endif // AABB_HPP
