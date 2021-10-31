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

extern std::vector <block_entry> blockreg;
extern int world_time;
FastNoiseLite n,n2;
long waterlvl=42;
bool init=false;
    double scrnoffx;
    double scrnoffy;
long long worldseed=-573947210;
void worldrendr(){
    SDL_GetRendererOutputSize(mainapp.renderer,&scrnw,&scrnh);
    long long blockcorner_x=(entity_list[0]->getpos().x)-(scrnw/2/64);
    long long blockcorner_y=(entity_list[0]->getpos().y)-(scrnh/2/64)+1;
    scrnoffx=entity_list[0]->getpos().x-(long long) (entity_list[0]->getpos().x);
    scrnoffy=round(entity_list[0]->getpos().y)-entity_list[0]->getpos().y;
    n.SetSeed((long long)worldseed);
    n2.SetSeed((long long)worldseed*12^1157  );
    bool watercheck=false,fillwater=false;
    for(long long x=-5;x<=(scrnw/64)+1;++x){
        double noiseval=n.GetNoise((double)blockcorner_x+x+(double)scrnoffx,(double)1024)*12+48;
        double noiseval2=n2.GetNoise((double)blockcorner_x+x+(double)scrnoffx,(double)1024)*10+10;
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
                        if(posy<noiseval/*basic terrain gen*/){
                            if(posy<=waterlvl&&noiseval2>4&&(posy+1)>=(n.GetNoise((double)blockcorner_x+x+(double)scrnoffx,(double)1024)*12+48)&&(*world_ref2)[absposx][posy+1].wassolid==0){
                                (*world_ref2)[absposx][posy].type=4;
                                (*world_ref2)[absposx][posy].wassolid=1;
                            }
                            else if (posy>(noiseval-14)){
                                (*world_ref2)[absposx][posy].type=2;
                                (*world_ref2)[absposx][posy].wassolid=1;


                            }
                            else{
                                (*world_ref2)[absposx][posy].type=3;
                                (*world_ref2)[absposx][posy].wassolid=1;

                            }
                        }
                        else{
                            (*world_ref2)[absposx][posy].type=0;
                            (*world_ref2)[absposx][posy].wassolid=1;

                        }
                        (*world_ref2)[absposx][posy].generated=1;
                        //water handling
                        if(posy==(waterlvl)){
                            if((*world_ref2)[absposx][posy].type==0&&(*world_ref2)[absposx][posy].waterfilled==0){
                                if(watercheck==false){
                                    if(noiseval2>13||((*world_ref2)[absposx-1][posy].type==5)||((*world_ref2)[absposx+1][posy].type==5)){
                                        fillwater=true;
                                        watercheck=true;
                                    }
                                    else{
                                        fillwater=false;
                                        watercheck=true;
                                    }
                                }

                            }
                            else{
                                watercheck=false;
                            }
                            if(fillwater){
                                long long i=posy;
                                while((i>(blockcorner_y-scrnh/64))&&i>0){
                                    if(((*world_ref2)[absposx][i].type!=0)){
                                        goto out;
                                    }
                                    (*world_ref2)[absposx][i].type=5;
                                    (*world_ref2)[absposx][i].wassolid=1;
                                    (*world_ref2)[absposx][i].waterfilled=1;
                                    --i;
                                }
                                out:;
                            }

                            else {
                                    for(long long i=posy;(i>(blockcorner_y-scrnh/64))&&i>0&&((*world_ref2)[absposx][i].type==0);--i){
                                       // (*world_ref2)[absposx][i].generated=1;
                                        (*world_ref2)[absposx][posy].waterfilled=1;
                                }
                            }
                        }
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
                    if((blockreg[(*world_ref)[absposx][posy].type].bitfield&0b1000000)){
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
