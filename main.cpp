#include <stdio.h>
#include <SDL.h>
#include <types.hpp>
#include <entity.hpp>
#include <iostream>
#include <utils.hpp>
#include <SDL_image.h>
#include <blocks.hpp>
#include <tick.hpp>
#include <pthread.h>
#include <entity/player.hpp>
SDL_Texture *tex,*mob,*font;
#define screensz_x 1024
#define screensz_y 640
app mainapp;
pthread_t gamethread;
extern std::vector<entity*> entity_list;
unsigned char* keystate;
unsigned long long tickselapsed=0;



int main()
{

    *((u128*)&mainapp)=0;
    SDL_Event e;
    SDL_Rect a1;
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init() ERROR" << std::endl;
        exit(1);
    }

    mainapp.window=SDL_CreateWindow("Minceraft",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screensz_x,screensz_y,0);
    if(!(mainapp.window))
    {
        std::cout << "SDL_CreateWindow ERROR"  << std::endl;
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    mainapp.renderer = SDL_CreateRenderer(mainapp.window, -1, SDL_RENDERER_ACCELERATED);
    if (!mainapp.renderer)
    {
        printf("SDL_CreateRenderer FAIL, ERROR=%ld \n",(long) SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawColor(mainapp.renderer, 0x87, 0xce, 0xeb, 255);
    SDL_RenderSetLogicalSize(mainapp.renderer, screensz_x, screensz_y);
    SDL_RenderClear(mainapp.renderer);
     mob=loadtex("mobs.png");
     tex=loadtex("tex.png");
    font=loadtex("font.png");
    pthread_create(&gamethread,NULL,game_thread, NULL);
    entity_list.push_back(new player(rand()%700+70,60));
    SDL_Rect block_clips[]={
    {96,16,16,16},
    {240,240,16,16}
    };
    register_block(0,0,0,(SDL_Rect){0,0,16,16},"Air");
    register_block(1,0,1,(SDL_Rect){16,0,16,16},"Grass");
    register_block(2,0,1,(SDL_Rect){32,0,16,16},"Dirt");
    register_block(3,0,1,(SDL_Rect){48,0,16,16},"Stone");
    register_block(4,0,1,(SDL_Rect){64,0,16,16},"Sand");
    register_block(5,0,0,(SDL_Rect) {80,0,16,16},"Water");

    while(1)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                goto quit;
            default:
                break;

            }
        }


        ren_tick();

    }
    quit:
    exit(0);
}


