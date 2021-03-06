#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED
#if defined(__WIN32) || defined(__linux__)
#include <SDL.h>
#endif
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
}__attribute__((packed));


#endif // TYPES_HPP_INCLUDED
