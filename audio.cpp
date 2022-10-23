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

std::mt19937 randgen(1234);
short* tone,*y;
std::vector <struct note> notes;

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

void sqrtonegen(unsigned int freq, unsigned int duty,short* buf, double volume){
    buf = ( short* )malloc(44100/freq*2);
    for(int i=0; i<44100/freq;++i){
        if(i<44100/freq*duty/100){
            buf[i]=32767 * volume;
        }
        else buf[i]=-32767 * volume;
    }
  //chunks.push_back(Mix_QuickLoad_RAW((unsigned char*)buf,44100/freq*2));

}

void playnoise(unsigned int durr, short mod, double volume){
    unsigned int len;
    short* buf = randtonegen(mod,volume, &len);
    notes.push_back((struct note){durr, NOISE, mod, 0, buf, Mix_QuickLoad_RAW((unsigned char*)buf,len),0,0,1});

}

extern int quitthread;
void* audio_thread(void* none){
   // sqrtonegen(293,50,tone,0.01);
   // randtonegen(1,tone,0.05);
//    Mix_PlayChannel(1,chunks[0],-1);
    while(1){
        if(quitthread){
            return 0;
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
