#include <string>
#include <types.hpp>
#include <SDL_mixer.h>
#ifndef API_HPP_INCLUDED
#define API_HPP_INCLUDED



void prints(u32 x,u32 y,const char* format, ...);
void prints(u32 x,u32 y,float xscale,float yscale,const char* format, ...);
void sysspec_init();
void sysspec_putimg(void* tex, rect *src, rect *des);
void* sysspec_loadtex(std::string file);
void sysspec_prints(u32 x,u32 y,float xscale,float yscale,const char* format, ...);
void    sysspec_clearscrn();
void    sysspec_updatescrn();
void sysspec_settextrans(void* tex, u8 alpha);
void sysspec_getscreensz(int* x,int* y);
void sysspec_setcolourmod(void* tex,u8 r,u8 g,u8 b);
int sysspec_poll();
void sysspec_checkquit();
int sysspec_getmousepos(int *x, int *y);
void sysspec_delay(double d);
unsigned char * sysspec_getkeystate();

#if defined(__MINGW32__) || defined(__linux__)
    #include <SDL.h>
    #define sysspec_mleft SDL_BUTTON_LMASK
    #define sysspec_key_r SDL_SCANCODE_D
    #define sysspec_key_l SDL_SCANCODE_A
    #define sysspec_key_run SDL_SCANCODE_LSHIFT
    #define sysspec_key_jump SDL_SCANCODE_SPACE
    #define sysspec_key_pause SDL_SCANCODE_ESCAPE
    #define sysspec_key_invbar0 SDL_SCANCODE_1
#endif

#endif // API_HPP_INCLUDED
