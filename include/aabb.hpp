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
        void expand(double x,double y);
        void move(double xa, double d);


        double minx,miny,maxx,maxy;
};

#endif // AABB_HPP
