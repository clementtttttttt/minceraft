#ifndef BLOCKS_HPP_INCLUDED
#define BLOCKS_HPP_INCLUDED
#include <SDL.h>
#include <vector>
struct block{
    unsigned char type;
    unsigned char blockdat;
    unsigned char blockdat2;
    unsigned char wassolid:1;
    unsigned char generated:1;
    unsigned char waterfilled:1;
    unsigned char cavegened:1;
    unsigned char light=7;//max=15;
}__attribute__((packed));
struct block_entry{
    unsigned char bitfield;  //HAVEGRAV,HAVECOLL,CUSTOMPHYS,unused x 5
    SDL_Rect tex;
    double cfriction,cgrav;
};
/*
if no collision then cfriction means the friction of moving in it and gravity of
being in it
if collision then cfriction means friction of surface and gravity does nothing

*/
void register_block(int val,char havegrav,SDL_Rect tex);
extern std::vector <block_entry> blockreg;

#endif // BLOCKS_HPP_INCLUDED
