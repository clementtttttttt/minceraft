#include <world.hpp>
#include <utils.hpp>
#include <vector>
#include <blocks.hpp>
#include <iostream>
#include "fastnoise.hpp"
#include "raycastshade.hpp"
extern app mainapp;
extern SDL_Texture* tex;

    int scrnw,scrnh;
std::vector<std::vector<block>> world;
SDL_Rect block_clips[]={
    {0,0,16,16},
    {16,0,16,16},
    {32,0,16,16},
    {48,0,16,16},
    {64,0,16,16},
    {80,0,16,16},
    {96,16,16,16},
    {240,240,16,16}
};
extern std::vector <block_entry> blockreg;
extern int world_time;
FastNoiseLite n;
bool init=false;
    double scrnoffx;
    double scrnoffy;
void worldrendr(){
    SDL_GetRendererOutputSize(mainapp.renderer,&scrnw,&scrnh);
    long long blockcorner_x=(entity_list[0]->getpos().x)-(scrnw/2/64);
    long long blockcorner_y=(entity_list[0]->getpos().y)-(scrnh/2/64)+1;
    scrnoffx=entity_list[0]->getpos().x-(long long) (entity_list[0]->getpos().x);
    scrnoffy=round(entity_list[0]->getpos().y)-entity_list[0]->getpos().y;
   n.SetSeed((long long)worldrendr);

    for(long long x=-5;x<=(scrnw/64)+1;++x){
        double noiseval=n.GetNoise((double)blockcorner_x+x+(double)scrnoffx,(double)1024)*10+50;
            long long posx=blockcorner_x+x+scrnoffx;

        for(long long y=0;y<=(scrnh/64)+1;++y){

            long long posy=blockcorner_y+y+scrnoffy;
                        if(posx>=0){

            std::vector<std::vector<block>>* world_ref2=&world;


            long long absposx=abs(posx);

            if(world_ref2->size()<(absposx+100)){
                    world_ref2->resize((absposx+100),std::vector<block>(100));

            }
            if(((absposx)<world_ref2->size() ) && (posy<(*world_ref2)[absposx].size()) && (posy)>0){

                    if((*world_ref2)[absposx][posy].generated==0){ //world generator
                        double cavenoiseval=0;
                        if(posy<noiseval/*basic terrain gen*/&&(cavenoiseval<45)){
                            if(posy<noiseval-20)
                                (*world_ref2)[absposx][posy].type=3;
                            else (*world_ref2)[absposx][posy].type=2;
                        }
                        else (*world_ref2)[absposx][posy].type=0;
                        (*world_ref2)[absposx][posy].generated=1;

                    }
                    int  c=(((double)((*world_ref2)[absposx][posy].light))/15)*255+4;
                    if(c>255){
                        c=255;
                    }
                    SDL_SetTextureColorMod(tex,c,c,c);

                    SDL_SetRenderDrawBlendMode(mainapp.renderer, SDL_BLENDMODE_ADD);

                    putblocc((*world_ref2)[absposx][posy].type,x*64-(scrnoffx*64),scrnh-(y*64+scrnoffy*64),64);

            }

            else putblocc(7,(x*64-scrnoffx*64),scrnh-(y*64+scrnoffy*64),64);



        }else  putblocc(7,(x*64-scrnoffx*64),scrnh-(y*64+scrnoffy*64),64);
        }
    }
                    compute_shade(blockcorner_x,blockcorner_y,entity_list[0]->getpos());

}
std::vector<aabb> block_coll;
void worldtick(){
    block_coll.clear();
    long long blockcorner_x=entity_list[0]->getpos().x-(scrnw/2/64);
    long long blockcorner_y=entity_list[0]->getpos().y-(scrnh/2/64)-1;

    for(long long x=-10;x<=(scrnw/64)+10;++x){
        for(long long y=0;y<=(scrnh/64)+10;++y){
            long long posx=blockcorner_x+x;

            long long posy=blockcorner_y+y;
            if(posx>=0){
            std::vector<std::vector<block>>* world_ref=&world;

            long long absposx=abs(posx);

            if(((absposx)<world_ref->size() ) && (posy+scrnoffy)>=0){
                    if((*world_ref)[absposx][posy].type!=0){
                        block_coll.push_back(aabb(posx,posy,absposx+1,posy+1));
                    }
                    switch((*world_ref)[absposx][posy].type){
                        case 2:
                            if((*world_ref)[absposx][posy+1].type==0){
                                (*world_ref)[absposx][posy].type=1;
                            }
                            break;
                        case 1:
                            if((*world_ref)[absposx][posy+1].type!=0){
                                (*world_ref)[absposx][posy].type=2;
                            }
                            break;
                    }
            }
            }

        }
    }

}
