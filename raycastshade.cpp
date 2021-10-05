#include "raycastshade.hpp"
#include "blocks.hpp"
#include "aabb.hpp"
#include <cmath>
#include "entity.hpp"
#include <utils.hpp>
#define deg *57.2958
#define rad *0.0174533
struct vec2 sun,moon;

aabb sun_aabb(0,0,0,0),moon_aabb(0,0,0,0);
extern std::vector<std::vector<block>> world;
extern int scrnw,scrnh;
extern std::vector<aabb> block_coll;
extern int world_time;
long long tmpx,tmpy;
//TODO: NEW IMPROVED RAY SYSTEM
extern "C"{
double fastsin(double val);
double fastcos(double val);

}

asm (
    R"(
        .globl fastsin
        .globl fastcos
        .section .data
            asmtmp: .quad 0,0
            asmtmp2: .quad 0,0
        .section .text
    fastsin:
        movq %xmm0,asmtmp(%rip)
        fldl asmtmp(%rip)
        fsin
        fstpl asmtmp(%rip)
        movq asmtmp(%rip),%xmm0
        ret
    fastcos:
        movq %xmm0,asmtmp2(%rip)
        fldl asmtmp2(%rip)
        fcos
        fstpl asmtmp2(%rip)
        movq asmtmp2(%rip),%xmm0
        ret
    )"
);

int rec_count=0;
int compute_ray(double orgx,double orgy,double direction,int light,int reflected,int reflectcount=100000000){//returns true when the ray hits player, false when ray gets to light==0 without hitting player eye, LIGHT SRC ONLY
    struct vec2 hitblock,ppos;

    double sy=fastcos(direction rad)*0.5;
    double sx=fastsin(direction rad)*0.5;
    double cx=orgx,cy=orgy;
    double d2=direction;
    ppos=entity_list[0]->getpos();
    int weakencounter=90;
    //oob check:((cx>=blockcorner_x)&&(cy>=blockcorner_y)&&(cx<(blockcorner_x+scrnw/64))&&(cy<(blockcorner_y+scrnh)/64))
    #define oob_check ((tmpx-30>0)&&(cx>=(tmpx-30))&&(cy<=(tmpy+2))&&(cx<(30+tmpx+scrnw/64))&&(cy>round(tmpy-scrnh/64)))
    while(light>0&&reflectcount!=0){
        if(!oob_check&&reflected){
            return 0;
        }
                       //     std::cout << oob_check<<std::endl;
        if(oob_check&&(world[cx][cy].type==0)){
            if(world[cx][cy].light<light)
                world[cx][cy].light=light;
        }
        if(oob_check &&(world[cx][cy].type!=0)){
            double newdir=180-direction;
            int shouldlight=0;
            --light;
            --light;

            for(double i=-88;i<=88;i+=44){
                shouldlight|=compute_ray(cx,cy+0.5,newdir+i,light,1,reflectcount-1);
            }
            if(shouldlight){
                if(world[cx][cy].light<light)
                    world[cx][cy].light=light;

                return 1;
            }
             return 0;
        }
        if((round(cx)==round(ppos.x))&&(round(cy)==round(ppos.y+1))){
                if(world[cx][cy].light<light)
                    world[cx][cy].light=light;

            return 1;
        }
        if(weakencounter==0){
            --light;
                weakencounter=90;


        }
        else{
            --weakencounter;
        }
        cx+=sx;
        cy+=sy;


    }
    #undef oob_check
    return 0;
}
int tempcount;
int sunmoon_radius=15;//1 unit=1 metre lol
void compute_shade(long long bx,long long by,struct vec2 p_pos){
    double sun_deg=(((double)world_time/24000*360));
    double moon_deg=(360- (double)world_time/24000*360-90-180);
    tmpx=bx;
    tmpy=by+scrnh/64;

    for(long long x=bx-5;x<(bx+(scrnw/64)+5);++x){
        for(long long y=by-2;y<(by+(scrnh/64)+5);++y){
            world[x][y].light=0;
        }

    }
    for(double x=bx-30-(scrnw/64);x<(bx+30+(scrnw/64));x+=1){
                compute_ray(x,tmpy+3,sun_deg,15,0);
    }


}
