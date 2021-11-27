#include <utils.hpp>
#include "gui/elements/image.hpp"

image::image(const char* path,u32 x,u32 y,u32 xs,u32 ys,u32 ixs,u32 iys){
    this->x=x;
    this->y=y;
    this->ixs=ixs;
    this->iys=iys;
    this->xs=xs;
    this->ys=ys;
    this->path=path;

}
void image::tick(){
    if(!this->init){
        this->i=loadtex(this->path);
        this->init=true;
    }
    SDL_Rect clip={this->x,this->y,this->xs,this->ys};
    SDL_Rect tex_cliip={0,0,this->ixs,this->iys};
    blit(this->i,&tex_cliip,&clip);

}
