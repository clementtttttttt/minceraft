#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED

#include <cmath>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#ifdef __SIZEOF_INT128__
typedef unsigned __int128 u128;
#endif

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef double f32;
typedef double f64;

typedef struct{
    int x,y,w,h;
}rect;

class vec2{
    public:
        double x,y;

    vec2(double x,double y){
        this->x=x;
        this->y=y;
    }
    vec2(){

    }

    friend bool operator==(const vec2& lhs,const vec2& rhs){
        return (lhs.x == lhs.y) && (rhs.x == rhs.y);
    }

    vec2(const vec2& other){
        this->x = other.x;
        this->y = other.y;
    }

    double distance(vec2  second){
        return sqrt(((this->x-second.x)*(this->x-second.x))+(this->y-second.y)*(this->y-second.y));
    }
}__attribute__((packed));


#endif // TYPES_HPP_INCLUDED
