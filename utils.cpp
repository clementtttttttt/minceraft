#include <utils.hpp>
#include <types.hpp>
#include <string>
#include <SDL_image.h>
#include <iostream>




extern app mainapp;

SDL_Texture* loadtex(std::string file){
    SDL_Texture* texture;
    texture=IMG_LoadTexture(mainapp.renderer, file.c_str());
    if(!texture){
        std::cout << "TEXTURE LOAD ERROR: "<< file << std::endl;
    }
    else std::cout << "TEXTURE LOADED SUCCESSFULLY:" << file << std::endl;
    return texture;
}


void blit(SDL_Texture *texture,SDL_Rect* clip,SDL_Rect* dest)
{

    SDL_RendererFlip flip=(clip->w<0)?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE;
        SDL_Rect b;
    memcpy(&b,clip,sizeof(b));
    clip->w=abs(clip->w);

    SDL_RenderCopyEx(mainapp.renderer,texture,clip,dest,NULL,NULL,flip);
    memcpy(clip,&b,sizeof(b));

}


void putblocc(u32 type,u32 x,u32 y,u32 sz){
    SDL_Rect rec{(int)x,(int)y,(int)sz,(int)sz};
    blit(tex,&block_clips[type],&rec);
}
