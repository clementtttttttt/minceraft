#include <blocks.hpp>
#include <iostream>
#include <string>
#include <types.hpp>
#include <utils.hpp>
#include <stdarg.h>
#include <api.hpp>



void putblocc(u32 type, u32 x, u32 y, u32 sz) {
  rect rec{(int)x, (int)y, (int)sz, (int)sz};
  sysspec_putimg((void*)tex, &blockreg[type].tex, &rec);
}

#pragma push
#pragma GCC diagnostic ignored "-Wnarrowing"
void putblocc(u32 type, u32 x, u32 y, u32 sz, u32 wlevel) {
  rect rec{(int)x, (int)y + ((float)sz * (1 - (float)wlevel / 16.0f)),
               (int)sz, (int)((float)sz * ((float)wlevel / 16.0f))};
  rect texrec{(int)blockreg[type].tex.x, (int)blockreg[type].tex.y,
                  (int)blockreg[type].tex.w, (int)blockreg[type].tex.w};
  sysspec_putimg((void*)tex, &texrec, &rec);
}




#pragma pop
