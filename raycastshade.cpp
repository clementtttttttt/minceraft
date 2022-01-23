#include "raycastshade.hpp"
#include "aabb.hpp"
#include "blocks.hpp"
#include "entity.hpp"
#include <cmath>
#include <pthread.h>
#include <utils.hpp>
#define deg *57.2958
#define rad *0.0174533
struct vec2 sun, moon;

aabb sun_aabb(0, 0, 0, 0), moon_aabb(0, 0, 0, 0);
extern std::vector<std::vector<block>> world,negworld;
extern int scrnw, scrnh;
extern std::vector<aabb> block_coll;
extern int world_time;
long long tmpx, tmpy;



// TODO: NEW IMPROVED RAY SYSTEM
extern "C" {
double *fastsincos(double val);
}
union cvert {
  double d;
  long long i;
};
static inline long long fround(double d) {

  cvert d2;
  d2.d = (d + 4503599627370496.0);
  d2.i <<= 13;
  d2.i >>= 13;
  return d2.i;
}

static inline double fastabs(double d) {
  cvert d2;
  d2.d = d;
  d2.i &= 0x7fffffffffffffff;
  return d2.d;
}

double diffuse_normal[] = {
    -20, 60,  50,  -62, -59, -65, -52, -8,  80,  -39, 85,  83,  -42, -24, -48,
    -26, -69, -72, -20, 55,  33,  -23, -16, -25, 27,  83,  -87, 42,  -30, -60,
    67,  79,  55,  -68, -49, -66, 56,  7,   -44, -42, 71,  -12, -33, -35, 6,
    90,  59,  -38, -66, 43,  42,  -65, -19, -44, -73, 25,  64,  63,  -27, 1,
    -70, -89, -55, -54, 79,  8,   20,  -74, -36, 25,  -15, -24, 54,  -79, -70,
    -82, -10, 80,  1,   72,  31,  -43, -60, -18, 11,  25,  -36, -81, -76, 16,
    34,  46,  -57, -2,  -66, 57,  52,  69,  -15, -20, 46,  34};

asm(
    R"(
        .globl fastsincos
        .globl fastsin

        .section .data
            asmtmp: .quad 0
            asmtmp2: .quad 0
        .section .text
    fastsincos:
        movq %xmm0,asmtmp(%rip)
        fldl asmtmp(%rip)
        fsincos
        fstpl asmtmp(%rip)
        fstpl asmtmp2(%rip)
        leaq asmtmp(%rip), %rax
        ret
    fastsin:
        movq %xmm0,asmtmp(%rip)
        fldl asmtmp(%rip)
        fsin
        fstpl asmtmp(%rip)
        movq asmtmp(%rip),%xmm0
        ret

    fastasin:
        movq %xmm0,asmtmp(%rip)
        fldl asmtmp(%rip)
        fsin
        fstpl asmtmp(%rip)
        movq asmtmp(%rip),%xmm0
        ret
    )");
extern "C"{
    double fastsin(double in);

}
double refangcalc(double iidx, double ridx, double ai) {
  return asin(iidx * fastsin(ai) / ridx)+(90 rad);
}

int rec_count = 0;
int compute_ray(
    double orgx, double orgy, double direction, int light, int reflected,
    int reflectcount =
        16) {

        // returns true when the ray hits player, false when ray gets to
              // light==0 without hitting player eye, LIGHT SRC ONLY
  struct vec2 hitblock, ppos;
  double *p = fastsincos(direction rad);
  double sx = p[1] * 0.5;
  double sy = p[0] * 0.5;
  double cx = orgx, cy = orgy;
  double d2 = direction;
  ppos = entity_list[0]->getpos();
  int weakencounter = 60;
  std::vector<vec2> air_list;
// oob
// check:((cx>=blockcorner_x)&&(cy>=blockcorner_y)&&(cx<(blockcorner_x+scrnw/64))&&(cy<(blockcorner_y+scrnh)/64))
#define oob_check                                                              \
  ((fastabs(cx) < world_ref->size()) && (cx >= (tmpx - 30)) && (cy <= (tmpy + 2)) &&             \
   (cx < (30 + tmpx + scrnw / 64)) && (cy > fround(tmpy - scrnh / 64)))
  double prevrefidx = 1;

  while (light > 0 && reflectcount != 0) {
    std::vector<std::vector<block>> *world_ref = cx>=0?&world:&negworld;

    if (!oob_check && reflected) return 0;
    //     std::cout << oob_check<<std::endl;

    if (oob_check &&(((*world_ref)[fastabs(cx)][cy].type == 5)))  {

      if ((*world_ref)[fastabs(cx)][cy].light < light) {
        air_list.push_back(vec2(cx, cy));
                         //(*world_ref)[cx][cy].light=light;

      }

    }
//    if (oob_check && (*world_ref)[fastabs(cx)][cy].light<light)  (*world_ref)[fastabs(cx)][cy].light=light;



    if (oob_check && (blockreg[(*world_ref)[fastabs(cx)][cy].type].bitfield & (1 << 6))) {

      double newdir = 180 - direction;
      int shouldlight = 0;
      --light;

      if (direction < 0) {
        direction = 360 + direction;
      }
      if (newdir < 0) {
        newdir = 360 + newdir;
      }
      int shouldcalc = 1;
      /*
                  if(direction>=0&&direction<90&&newdir>=90&&newdir<180&&shouldcalc){
                      for(double i=92;i<=268;i+=44){
                          shouldlight|=compute_ray(cx,cy-1,i,light,1,reflectcount-1);
                      }
                      shouldcalc=0;
                  }
                  if(direction>=90&&direction<180&&newdir>=0&&newdir<90&&shouldcalc){
                      for(double i=-84;i<=84;i+=3.5){
                      shouldlight|=compute_ray(cx,cy+1,i,light,1,reflectcount-1);
                      }
                      shouldcalc=0;

                  }
                  if(direction>=180&&direction<270&&newdir>=270&&newdir<360&&shouldcalc){
                      for(double i=-84;i<=84;i+=3.5){
                          shouldlight|=compute_ray(cx,cy+1,i,light,1,reflectcount-1);
                      }
                      shouldcalc=0;

                  }
                  if(direction>=90&&direction<180&&newdir>=180&&newdir<270&&shouldcalc){
                      for(double i=2;i<=178;i+=44){
                          shouldlight|=compute_ray(cx-1,cy,i,light,1,reflectcount-1);
                      }
                      shouldcalc=0;

                  }
                  if(direction>=270&&direction<360&&newdir>=180&&newdir<270&&shouldcalc){
                      for(double i=92;i<=268;i+=44){
                          shouldlight|=compute_ray(cx+1,cy,i,light,1,reflectcount-1);
                      }
                      shouldcalc=0;

                  }

      */
      double unused;

      if (direction >= 0 && direction < 90 && newdir >= 90 && newdir < 180 &&
          shouldcalc) {
        double f = modf(cx, &unused) * 100;
        shouldlight |= compute_ray(cx, cy - 1, 180 + (diffuse_normal[(long)f]),
                                   light, 1, reflectcount - 1);

        shouldcalc = 0;
      }
      if (direction >= 90 && direction < 180 && newdir >= 0 && newdir < 90 &&
          shouldcalc) {
        double f = modf(cx, &unused) * 100;

        shouldlight |= compute_ray(cx, cy + 1, (diffuse_normal[(long)f]), light,
                                   1, reflectcount - 1);

        shouldcalc = 0;
      }
      if (direction >= 180 && direction < 270 && newdir >= 270 &&
          newdir < 360 && shouldcalc) {
        double f = modf(cx, &unused) * 100;
        shouldlight |= compute_ray(cx, cy + 1, -(diffuse_normal[(long)f]),
                                   light, 1, reflectcount - 1);

        shouldcalc = 0;
      }
      if (direction >= 0 && direction < 90 && newdir >= 270 && newdir < 360 &&
          shouldcalc) {
        double f = modf(cy, &unused) * 100;

        shouldlight |= compute_ray(cx - 1, cy, 90 + (diffuse_normal[(long)f]),
                                   light, 1, reflectcount - 1);

        shouldcalc = 0;
      }
      if (direction >= 90 && direction < 180 && newdir >= 180 && newdir < 270 &&
          shouldcalc) {
        double f = modf(cy, &unused) * 100;

        shouldlight |= compute_ray(cx - 1, cy, 90 + (diffuse_normal[(long)f]),
                                   light, 1, reflectcount - 1);

        shouldcalc = 0;
      }
      if (direction >= 270 && direction < 360 && newdir >= 180 &&
          newdir < 270 && shouldcalc) {
        double f = modf(cy, &unused) * 100;
        shouldlight |= compute_ray(cx + 1, cy, 180 + (diffuse_normal[(long)f]),
                                   light, 1, reflectcount - 1);

        shouldcalc = 0;
      }

      if (shouldlight) {
        if ((*world_ref)[fastabs(cx)][cy].light < light) {
          (*world_ref)[fastabs(cx)][cy].light = light;
        }
        for (int i = 0; i < air_list.size(); ++i) {
          if ((*world_ref)[fastabs(air_list[i].x)][air_list[i].y].light < light)
            (*world_ref)[fastabs(air_list[i].x)][air_list[i].y].light = light;
        }

        return 1;
      }
      return 0;
    }
    //water
    if (oob_check && blockreg[(*world_ref)[fastabs(cx)][cy].type].refindex != prevrefidx) {
        if (direction < 0) {
          direction = 360 + direction;
        }
      double refang = refangcalc(prevrefidx, blockreg[(*world_ref)[fastabs(cx)][cy].type].refindex, direction rad);
      if (std::isnan(refang)) {
        int shouldlight = 0;
        double unused;

        double newdir = 180 - direction;
        if (direction < 0) {
          direction = 360 + direction;
        }
        if (newdir < 0) {

          newdir = 360 + newdir;
        }
        int shouldcalc = 1;
        {
          if (direction >= 0 && direction < 90 && newdir >= 90 &&
              newdir < 180 && shouldcalc) {
            double f = modf(cx, &unused) * 100;
            shouldlight |=
                compute_ray(cx, cy - 1, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
          if (direction >= 90 && direction < 180 && newdir >= 0 &&
              newdir < 90 && shouldcalc) {
            double f = modf(cx, &unused) * 100;

            shouldlight |=
                compute_ray(cx, cy + 1, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
          if (direction >= 180 && direction < 270 && newdir >= 270 &&
              newdir < 360 && shouldcalc) {
            double f = modf(cx, &unused) * 100;
            shouldlight |=
                compute_ray(cx, cy + 1, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
          if (direction >= 0 && direction < 90 && newdir >= 270 &&
              newdir < 360 && shouldcalc) {
            double f = modf(cy, &unused) * 100;

            shouldlight |=
                compute_ray(cx - 1, cy, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
          if (direction >= 90 && direction < 180 && newdir >= 180 &&
              newdir < 270 && shouldcalc) {
            double f = modf(cy, &unused) * 100;

            shouldlight |=
                compute_ray(cx - 1, cy, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
          if (direction >= 270 && direction < 360 && newdir >= 180 &&
              newdir < 270 && shouldcalc) {
            double f = modf(cy, &unused) * 100;
            shouldlight |=
                compute_ray(cx + 1, cy, newdir, light, 1, reflectcount - 1);

            shouldcalc = 0;
          }
        }

        if (shouldlight) {
          if ((*world_ref)[fastabs(cx)][cy].light < light) {
            (*world_ref)[fastabs(cx)][cy].light = light;
          }
          for (int i = 0; i < air_list.size(); ++i) {
            if ((*world_ref)[fastabs(air_list[i].x)][air_list[i].y].light < light)
              (*world_ref)[fastabs(air_list[i].x)][air_list[i].y].light = light;
          }
          return 1;
        }
        return 0;

      } else {
        if (refang < 0) {
          refang = (360 rad) + refang;
        }
        p = fastsincos(refang);
        sx = p[1] * 0.5;
        sy = p[0] * 0.5;
        direction=refang deg;
        d2=refang deg;
      }
    }
    if (((fround(cx) == fround(ppos.x)) && (fround(cy) == fround(ppos.y + 1)))||((fround(cx) == fround(ppos.x)) && (fround(cy) == fround(ppos.y)))) {
      if ((*world_ref)[fastabs(cx)][cy].light < light)
        (*world_ref)[fastabs(cx)][cy].light = light;

      return 1;
    }
    if (weakencounter == 0) {

      --light;
      weakencounter = 60;

    } else {
      --weakencounter;
    }
    prevrefidx = oob_check ? (blockreg[(*world_ref)[fastabs(cx)][cy].type].refindex) : 1;
    cx += sx;
    cy += sy;
  }
#undef oob_check
  return 0;
}
pthread_t rtxthreado;
double globx, globlsundeg;
void *rtxthread(void *unused) {

  for (double x = ((globx + ((scrnw / 64)) / 2)); x < ((globx + 4    + (scrnw / 64))); x += 0.02) {
    compute_ray(x, tmpy + 0.5, globlsundeg, 15, 0);
  }
  return 0;
}
int tempcount;
int sunmoon_radius = 15; // 1 unit=1 metre lol
void compute_shade(long long bx, long long by, struct vec2 p_pos) {
  double sun_deg = (((double)world_time / 24000 * 360));
  globlsundeg = sun_deg;

  double moon_deg = (360 - (double)world_time / 24000 * 360 - 90 - 180);
  tmpx = bx;
  tmpy = by + scrnh / 64;
  globx = bx;
  char envlight = 15;
  if (sun_deg < 90 && sun_deg > 270) {
    envlight = 4;
  }


  for (long long x = bx - 5; x < ((bx + (scrnw / 64) + 5)); ++x) {
    for (long long y = by - 2; y < (by + (scrnh / 64) + 5); ++y) {
        std::vector<std::vector<block>> *world_ref = x>=0?&world:&negworld;
      if(fastabs(x)<world_ref->size())
      if ((*world_ref)[fastabs(x)][y].type == 0) {
        (*world_ref)[fastabs(x)][y].light = envlight;
      } else
        (*world_ref)[fastabs(x)][y].light = 0;
    }
  }
  pthread_create(&rtxthreado, NULL, rtxthread, NULL);

  for (double x = bx - 13;
       x < (bx + ((scrnw / 64)) / 2); x += 0.02) {
        compute_ray(x, tmpy + 0.5, sun_deg, 15, 0);

  }
  pthread_join(rtxthreado, NULL);
}
