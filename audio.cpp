#include <SDL_mixer.h>
#include <vector>
#include <random>
#include <api.hpp>
#include <audio.hpp>
/*
typedef struct Mix_Chunk {
    int allocated;
    Uint8 *abuf;
    Uint32 alen;
    Uint8 volume;       per sample volume 0-128
} Mix_Chunk;

*/

typedef struct songnote song[][10];

#define TEMPO 120

song snowman={
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,E3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),5,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,E3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),5,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,E3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,B3F,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,F3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),5,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,E3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,E3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,C1S,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,C1,NTM(HALF),50,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,G3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,B1,NTM(QUARTER),50,0.6,NTM(QUARTER)},(struct songnote){1,NOISE,6,NTM(QUARTER),50,0.3,NTM(QUARTER)}},
    {(struct songnote){1,SQR,C4,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,G3,NTM(HALF),50,1,NTM(HALF)},(struct songnote){1,SQR,B1F,NTM(HALF),5,0.6,NTM(HALF)},(struct songnote){1,NOISE,1,NTM(HALF),50,0.3,NTM(HALF)}},
    {(struct songnote){1,SQR,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,NOISE,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,EMPTY,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,SQR,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,NOISE,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,SQR,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,NOISE,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,EMPTY,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,SQR,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,NOISE,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,SQR,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,NOISE,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,EMPTY,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,SQR,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,NOISE,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,EMPTY,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,SQR,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,SQR,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,NOISE,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,EMPTY,D4,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,A3,NTM(EIGHTH),50,1,NTM(EIGHTH)},(struct songnote){1,EMPTY,F4,NTM(EIGHTH),50,0.5,NTM(EIGHTH)},(struct songnote){1,EMPTY,1,NTM(EIGHTH),50,0.5,NTM(EIGHTH)}},
    {(struct songnote){1,SQR,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,NOISE,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,SQR,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,NOISE,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,SQR,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,SQR,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,NOISE,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},
    {(struct songnote){1,EMPTY,D4,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,A3,NTM(QUARTER),50,1,NTM(QUARTER)},(struct songnote){1,EMPTY,F4,NTM(QUARTER),50,0.5,NTM(QUARTER)},(struct songnote){1,EMPTY,1,NTM(QUARTER),50,0.5,NTM(QUARTER)}},

    {{0}}


};

#undef TEMPO


std::mt19937 randgen(1234);
short* tone,*y;
std::vector <struct note> notes;

std::vector <song*> currentsongs{};

std::uniform_int_distribution<> normal_dist(0,1);

short past=0;
short* randtone = ( short*)malloc(65536);

short* randtonegen(short mod, double volume, unsigned int *len){
    randtone = ( short*)malloc(65536);
    for(int i=0;i<32768;++i){
        if(i%mod == 0)
            randtone[i] = past = normal_dist(randgen)*32767*volume;
        else randtone[i] = past;
      //  printf("%i\n",randtone[i]);
    }
    *len = 65536;
    //chunks.push_back(Mix_QuickLoad_RAW((unsigned char*)tone,65536));
    return randtone;
}

short* sqrtonegen(unsigned int freq, unsigned int duty, double volume, unsigned int *len){
    short* buf = ( short* )malloc(44100/freq*2);
    for(int i=0; i<44100/freq;++i){
        if(i<44100/freq*duty/100){
            buf[i]=32767 * volume;
        }
        else buf[i]=-32767 * volume;
    }

    *len = 44100/freq*2;
    //chunks.push_back(Mix_QuickLoad_RAW((unsigned char*)buf,44100/freq*2));
    return buf;
}

short* tritonegen(unsigned int freq, double volume, unsigned int *len){
    short* buf = ( short* )malloc(((44100/freq) + (44100/freq))*2);
    double step = 32768/(44100/freq/2)*volume;
    double counter = 0;
    for(int dir=0; dir<2; ++dir){
        for(int i=(44100/freq*dir); i<44100/freq+(44100/freq*dir);++i){
            if((i-(44100/freq*dir)) < (44100/freq/2)){
                buf[i] = counter = (dir==1 ? counter + step : counter - step);

            }
            else{
                buf[i] = counter = (dir==1 ? counter - step : counter + step);
            }
        }
    }
    *len = ((44100/freq) + (44100/freq))*2;
    //chunks.push_back(Mix_QuickLoad_RAW((unsigned char*)buf,44100/freq*2));
    return buf;
}


void playnoise(unsigned int durr, short mod, double volume){
    unsigned int len;
    short* buf = randtonegen(mod,volume, &len);
    notes.push_back((struct note){durr, NOISE, (unsigned int)mod, 0, buf, Mix_QuickLoad_RAW((unsigned char*)buf,len),0,0,1});

}


void playsqr(unsigned int durr, unsigned int freq, unsigned int duty, double volume){
    unsigned int len;
    short* buf = sqrtonegen(freq, duty, volume, &len);
    notes.push_back((struct note){durr, SQR, freq, 0, buf, Mix_QuickLoad_RAW((unsigned char*)buf,len),0,0,1});

}

void playtri(unsigned int durr, unsigned int freq, double volume){
    unsigned int len;
    short* buf = tritonegen(freq, volume, &len);
    notes.push_back((struct note){durr, SQR, freq, 0, buf, Mix_QuickLoad_RAW((unsigned char*)buf,len),0,0,1});

}

unsigned int noteindex[10];

extern int quitthread;
void* audio_thread(void* none){
   // sqrtonegen(293,50,tone,0.01);
   // randtonegen(1,tone,0.05);
//    Mix_PlayChannel(1,chunks[0],-1);/
    while(1){
        if(quitthread){
            return 0;
        }

        for(int i=0;i<currentsongs.size();++i){
            for(int j=0;j<10;++j){
                #define curr (*(currentsongs[i]))[noteindex[j]][j]
                if(curr.valid){
                    if(curr.durrc > 0){
                        if(!curr.playin){
                            switch(curr.type){
                                case EMPTY:
                                    break;
                                case SQR:
                                    playsqr(curr.durr,curr.pitch,curr.specval, curr.vol);
                                    break;
                                case NOISE:
                                    playnoise(curr.durr,curr.pitch,curr.vol);
                                    break;
                                case TRI:
                                    playtri(curr.durr,curr.pitch,curr.vol);
                                    break;
                            }
                            curr.playin=1;
                        }
                    }
                    else {
                        ++(noteindex[j]);
                    }
                    --curr.durrc;
                }
                else{
                    if(j == 0){
                        currentsongs.erase(currentsongs.begin()+i);
                        break;
                    }
                }
                #undef curr
            }
        }


        for(int i=0;i<notes.size();++i){
            if(notes[i].playing == 0){
                notes[i].channel=Mix_PlayChannel(-1,notes[i].chunk,-1);
                notes[i].playing = 1;
            }
            --notes[i].durr;
            if(notes[i].durr == 0){
                Mix_HaltChannel(notes[i].channel);
                free(notes[i].chunk->abuf);
                Mix_FreeChunk(notes[i].chunk);
                notes.erase(notes.begin()+i);
            }
        }

        sysspec_delay(4);
    }
}
