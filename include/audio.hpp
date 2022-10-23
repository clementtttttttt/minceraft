#ifndef AUDIO_HPP_INCLUDED
#define AUDIO_HPP_INCLUDED
#include <SDL_mixer.h>
enum notetypes{
    EMPTY, SQR, NOISE

};

struct note{
    unsigned int durr;
    unsigned int type;
    unsigned int pitch;
    unsigned int duty;
    short* buf;
    Mix_Chunk* chunk;
    unsigned int channel;
    unsigned int playing;
    unsigned int allocated;
};

void* audio_thread(void* none);
void playnoise(unsigned int durr, short mod, double volume);

#endif // AUDIO_HPP_INCLUDED
