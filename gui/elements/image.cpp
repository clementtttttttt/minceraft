#include <utils.hpp>
#include "gui/elements/image.hpp"

image::image(const char* path,u32 x,u32 y,u32 xs,u32 ys,u32 ixs,u32 iys,u8 transparency){
    this->x=x;
    this->y=y;
    this->ixs=ixs;
    this->iys=iys;
    this->xs=xs;
    this->ys=ys;
    this->path=path;
    this->transparency=transparency;

}
void image::tick(){
    if(!this->init){
        this->i=loadtex(this->path);
        this->init=true;
    }

    SDL_Rect clip={(int)this->x,(int)this->y,(int)this->xs,(int)this->ys};
    SDL_Rect tex_cliip={0,0,(int)this->ixs,(int)this->iys};
    SDL_SetTextureAlphaMod(this->i, this->transparency );
    blit(this->i,&tex_cliip,&clip);

}
