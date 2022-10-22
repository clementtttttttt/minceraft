#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED
#include <SDL.h>
#include <string>
#include <types.hpp>
#include <chrono>
#define screensz_x 1024
#define screensz_y 768
#define timer_start                     auto start=std::chrono::high_resolution_clock::now();
#define timer_stop                    auto stop=std::chrono::high_resolution_clock::now();
#define print_time std::cout << duration_cast<std::chrono::microseconds>(stop-start).count()<<std::endl;
#define timer_val std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count()

#define PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286

extern rect block_clips[];

extern void* tex,*font;
void putblocc(u32 type,u32 x,u32 y,u32 sz=96);
void putblocc(u32 type,u32 x,u32 y,u32 sz,u32 wlevel);
void putfont(char in,u32 x,u32 y);


#endif // UTILS_HPP_INCLUDED
