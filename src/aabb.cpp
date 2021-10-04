#include "aabb.hpp"
#include <iostream>
aabb::aabb(double minx,double miny,double maxx,double maxy)
{
    //ctor
    this->minx=minx;
    this->miny=miny;
    this->maxx=maxx;
    this->maxy=maxy;
}
void aabb::expand(double xm,double ym){
    if(xm<0){
        this->minx+=xm;
    }
    if(xm>0){
        this->maxx+=xm;
    }
    if(ym<0){
        this->miny+=ym;
    }
    if(ym>0){
        this->maxy+=ym;
    }

}
void aabb::move(double xa, double d) {
      this->minx += xa;
      this->miny += d;
      this->maxx += xa;
      this->maxy += d;
}
double aabb::clipXCollide(aabb c, double xa) {
      if(c.maxy > this->miny && c.miny < this->maxy) {
            double max;
            if(xa > 0.0D && c.maxx <= this->minx) {
               max = this->minx - c.maxx;
               if(max < xa) {
                  xa = max;
               }
            }

            if(xa < 0.0D && c.minx >= this->maxx) {
               max = this->maxx - c.minx;
               if(max > xa) {
                  xa = max;
               }
            }
            return xa;

      } else {
         return xa;
      }
   }

double aabb::clipYCollide(aabb c, double ya) {
      if(c.maxx > this->minx && c.minx < this->maxx) {
            double max;
            if(ya > 0.0D && c.maxy <= this->miny) {
               max = this->miny - c.maxy;
               if(max < ya) {
                  ya = max;
               }
            }

            if(ya < 0.0D && c.miny >= this->maxy) {
               max = this->maxy - c.miny;
               if(max > ya) {
                  ya = max;
               }
            }

            return ya;

      } else {
         return ya;
      }
   }
