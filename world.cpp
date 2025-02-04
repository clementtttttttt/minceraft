#include "fastnoise.hpp"
#include "raycastshade.hpp"
#include <api.hpp>
#include <blocks.hpp>
#include <iostream>
#include <utils.hpp>
#include <vector>
#include <world.hpp>

#include "entity/pig.hpp"
extern void *tex;
// NOTE: USE TRUNCF INSTEAD OF ROUNDING!!!
int scrnw, scrnh;
std::vector<std::vector<block> > world (1000, std::vector<block> (200)),
    negworld (1000, std::vector<block> (200));

extern std::vector<block_entry> blockreg;
extern int world_time;
FastNoiseLite n, n2;
long waterlvl = 42;
bool init = false;
double scrnoffx;
double scrnoffy;
long long worldseed = 4202639445;
double prevx;
void
worldrendr ()
{
  sysspec_getscreensz (&scrnw, &scrnh);
  long long blockcorner_x
      = (truncf (entity_list[0]->getpos ().x) - (scrnw / 2 / 64));
  long long blockcorner_y
      = (entity_list[0]->getpos ().y) - (scrnh / 2 / 64) ;
  scrnoffx
      = entity_list[0]->getpos ().x - (long long)(entity_list[0]->getpos ().x);
  scrnoffy = -( ((entity_list[0]->getpos ().y) - truncf(entity_list[0]->getpos ().y)));
  n.SetSeed ((long long)worldseed);
  n2.SetSeed ((long long)worldseed * 12 ^ 1157);
  bool watercheck = false, fillwater = false;
  for (long long x = -5; x <= (scrnw / 64) + 1; ++x)
    {
      double noiseval
          = n.GetNoise ((double)blockcorner_x + x + (double)scrnoffx,
                        (double)1024)
                * 12
            + 48;
      double noiseval2
          = n2.GetNoise ((double)blockcorner_x + x + (double)scrnoffx,
                         (double)1024)
                * 10
            + 10;
      long long posx = (blockcorner_x + x);
      std::vector<std::vector<block> > *world_ref2
          = (posx >= -0.99) ? &world : &negworld;

      for (long long y = 0; y <= (scrnh / 64) + 1; ++y)
        {
//            std::cout << scrnoffy << std::endl;
          long long posy = blockcorner_y + y;

          long long absposx = abs (posx);
          if (world_ref2->size () < (absposx + 100))
            {
              world_ref2->resize ((absposx + 100), std::vector<block> (200));
            }
          if (((absposx) < world_ref2->size ())
              && (posy < (*world_ref2)[absposx].size ()) && (posy) > 0)
            {

              if ((*world_ref2)[absposx][posy].generated == 0)
                { // world generator
                  double cavenoiseval = 0;
                  if (posy < noiseval /*basic terrain gen*/)
                    {
                      if (posy <= waterlvl && noiseval2 > 4
                          && (posy + 1)
                                 >= (n.GetNoise ((double)blockcorner_x + x
                                                     + (double)scrnoffx,
                                                 (double)1024)
                                         * 12
                                     + 48)
                          && (*world_ref2)[absposx][posy + 1].wassolid == 0)
                        {
                          (*world_ref2)[absposx][posy].type = 4;
                          (*world_ref2)[absposx][posy].wassolid = 1;
                        }
                      else if (posy > (noiseval - 14))
                        {
                          (*world_ref2)[absposx][posy].type = 2;
                          (*world_ref2)[absposx][posy].wassolid = 1;
                        }
                      else
                        {
                          (*world_ref2)[absposx][posy].type = 3;
                          (*world_ref2)[absposx][posy].wassolid = 1;
                        }
                    }
                  else
                    {
                      (*world_ref2)[absposx][posy].type = 0;
                      (*world_ref2)[absposx][posy].wassolid = 1;
                    }
                  (*world_ref2)[absposx][posy].generated = 1;
                  (*world_ref2)[absposx][posy].created_timestamp
                      = std::time (nullptr);
                  // water handling
                  if (posy == (waterlvl))
                    {
                      if ((*world_ref2)[absposx][posy].type == 0
                          && (*world_ref2)[absposx][posy].waterfilled == 0)
                        {
                          if (watercheck == false)
                            {
                              if (noiseval2 > 13
                                  || ((*world_ref2)[absposx - 1][posy].type
                                      == 5)
                                  || ((*world_ref2)[absposx + 1][posy].type
                                      == 5))
                                {
                                  fillwater = true;
                                  watercheck = true;
                                }
                              else
                                {
                                  fillwater = false;
                                  watercheck = true;
                                }
                            }
                        }
                      else
                        {
                          watercheck = false;
                        }
                      if (fillwater)
                        {
                          long long i = posy;
                          while ((i > (blockcorner_y - scrnh / 64)) && i > 0)
                            {
                              if (((*world_ref2)[absposx][i].type != 0))
                                {
                                  goto out;
                                }
                              (*world_ref2)[absposx][i].type = 5;
                              (*world_ref2)[absposx][i].wassolid = 1;
                              (*world_ref2)[absposx][i].waterfilled = 1;
                              (*world_ref2)[absposx][i].blockdat2 = 1;
                              (*world_ref2)[absposx][i].blockdat = 16;

                              --i;
                            }
                        out:;
                        }

                      else
                        {
                          for (long long i = posy;
                               (i > (blockcorner_y - scrnh / 64)) && i > 0
                               && ((*world_ref2)[absposx][i].type == 0);
                               --i)
                            {
                              (*world_ref2)[absposx][posy].waterfilled = 1;
                            }
                        }
                    }
                }
              int c
                  = (((double)((*world_ref2)[absposx][posy].light)) / 15) * 255
                    + 4;
              if (c > 255)
                {
                  c = 255;
                }
              sysspec_setcolourmod (tex, c, c, c);

              if ((*world_ref2)[absposx][posy].type != 5)
                putblocc ((*world_ref2)[absposx][posy].type,
                          x * 64 - (scrnoffx * 64),
                          scrnh - (y * 64 + scrnoffy * 64), 64);
              else
                {
                  putblocc ((*world_ref2)[absposx][posy].type,
                            x * 64 - (scrnoffx * 64),
                            scrnh - (y * 64 + scrnoffy * 64), 64,
                            (((*world_ref2)[absposx][posy + 1].type != 5
                                  ? (*world_ref2)[absposx][posy].blockdat
                                  : 16)));
                }
            }

          else
            putblocc (7, (x * 64 - scrnoffx * 64),
                      scrnh - (y * 64 + scrnoffy * 64), 64);
        }
      prevx = posx;
    }
  compute_shade (blockcorner_x, blockcorner_y, entity_list[0]->getpos ());
}
std::vector<aabb> block_coll;

block getBlock(double x, double y){
      std::vector<std::vector<block> > *world_ref
          = x >= -0.99 ? &world : &negworld;
    return (*world_ref)[abs(truncf(x))][truncf(y)];
}

block_entry getBlockType(double x, double y){
      std::vector<std::vector<block> > *world_ref
          = x >= -0.99 ? &world : &negworld;
    return blockreg[(*world_ref)[abs(truncf(x))][truncf(y)].type];
}




void
worldtick ()
{

  block_coll.clear ();
  long long blockcorner_x
      = truncf (entity_list[0]->getpos ().x) - (scrnw / 2 / 64);
  long long blockcorner_y = entity_list[0]->getpos ().y - (scrnh / 2 / 64);
            if( (world_time % 100 == 0) && entity_list.size() < 2){
                entity_list.push_back(new pig(entity_list[0]->getpos().x, entity_list[0]->getpos().y));
            }
  for (long long x = -10; x <= (scrnw / 64) + 10; ++x)
    {
      long long posx = blockcorner_x + x;

      std::vector<std::vector<block> > *world_ref
          = posx >= -0.99 ? &world : &negworld;
      std::vector<std::vector<block> > *world_ref2
          = (posx - 1) >= -0.99 ? &world : &negworld;
      std::vector<std::vector<block> > *world_ref3
          = (posx + 1) >= -0.99 ? &world : &negworld;

      for (long long y = 0; y <= (scrnh / 64) + 10; ++y)
        {


          long long posy = blockcorner_y + y;

          long long absposx = abs (posx);
          long long absposx2 = abs (posx - 1);
          long long absposx3 = abs (posx + 1);

          if (((absposx) < world_ref->size ()) && (posy + scrnoffy) >= 0
              && posy < (*world_ref)[absposx].size ())
            {
              if ((blockreg[(*world_ref)[absposx][posy].type].bitfield
                   & 0b1000000))
                {
                  block_coll.push_back (aabb (posx, posy, posx + 1, posy + 1));
                }

              switch ((*world_ref)[absposx][posy].type)
                {
                case 2:
                  if ((*world_ref)[absposx][posy + 1].type == 0)
                    {
                      (*world_ref)[absposx][posy].type = 1;
                    }
                  break;
                case 1:
                  if ((*world_ref)[absposx][posy + 1].type != 0)
                    {
                      (*world_ref)[absposx][posy].type = 2;
                    }
                  break;
                case 5:
                  if ((*world_ref)[absposx][posy].blockdat == 0)
                    {
                      (*world_ref)[absposx][posy].type = 0;
                      (*world_ref)[absposx][posy].blockdat = 0;
                    }
                  else
                    {
                      if ((*world_ref)[absposx][posy - 1].type == 0)
                        {
                          (*world_ref)[absposx][posy - 1].type = 5;
                          (*world_ref)[absposx][posy - 1].blockdat = 0;
                        }
                      if ((*world_ref)[absposx][posy - 1].generated
                          && (*world_ref)[absposx][posy - 1].type == 5
                          && (*world_ref)[absposx][posy - 1].blockdat != 16
                          && (*world_ref)[absposx][posy].blockdat > 0)
                        {
                          (*world_ref)[absposx][posy - 1].blockdat += 1;
                          (*world_ref)[absposx][posy].blockdat -= 1;
                        }
                      else if ((*world_ref)[absposx][posy].blockdat != 0)
                        {
                          if ((*world_ref3)[absposx3][posy].type == 0
                              && (*world_ref3)[absposx3][posy].generated)
                            {
                              (*world_ref3)[absposx3][posy].type = 5;
                              (*world_ref3)[absposx3][posy].blockdat = 0;
                            }
                          if ((absposx - 1) < world_ref2->size ())
                            {
                              if ((*world_ref2)[absposx2][posy].type == 0
                                  && (*world_ref2)[absposx2][posy].generated)
                                {
                                  (*world_ref2)[absposx2][posy].type = 5;
                                  (*world_ref2)[absposx2][posy].blockdat = 0;
                                }
                              if ((*world_ref2)[absposx2][posy].generated
                                  && ((*world_ref2)[absposx2][posy].blockdat
                                      < (*world_ref)[absposx][posy].blockdat)
                                  && (*world_ref2)[absposx2][posy].type == 5
                                  && (*world_ref2)[absposx2][posy].blockdat
                                         != 16
                                  && (*world_ref)[absposx][posy].blockdat > 0)
                                {
                                  (*world_ref2)[absposx2][posy].blockdat += 1;
                                  (*world_ref)[absposx][posy].blockdat -= 1;
                                }
                            }
                          if ((*world_ref3)[absposx3][posy].generated
                              && ((*world_ref3)[absposx3][posy].blockdat
                                  < (*world_ref)[absposx][posy].blockdat)
                              && (*world_ref3)[absposx3][posy].type == 5
                              && (*world_ref3)[absposx3][posy].blockdat != 16
                              && (*world_ref)[absposx][posy].blockdat > 0)
                            {
                              (*world_ref3)[absposx3][posy].blockdat += 1;
                              (*world_ref)[absposx][posy].blockdat -= 1;
                            }
                        }
                    }

                  break;
                }
            }
        }
    }
}
