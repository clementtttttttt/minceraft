#ifndef AUDIO_HPP_INCLUDED
#define AUDIO_HPP_INCLUDED
#include <SDL_mixer.h>
enum notetypes{
    EMPTY, SQR, NOISE, TRI

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

struct songnote{
    unsigned int valid;
    unsigned int type;
    unsigned int pitch;
    unsigned int durr;
    unsigned int specval;
    double vol;
    unsigned int durrc;
    unsigned int playin;


};

void* audio_thread(void* none);
void playnoise(unsigned int durr, short mod, double volume);


// Taken from http://www.phy.mtu.edu/~suits/notefreqs.html
// Rounded to nearest number
// Format: <note><octave>(sharp/flat)
//    Ex: C5S = C# note in 5th octave
#define C0     16
#define C0S    17
#define D0F   C0S
#define D0     18
#define D0S    19
#define E0F   D0S
#define E0     21
#define F0     22
#define F0S    23
#define G0F   F0S
#define G0     25
#define G0S    26
#define A0F   G0S
#define A0     28
#define A0S    29
#define B0F   A0S
#define B0     31
#define C1     33
#define C1S    35
#define D1F   C1S
#define D1     37
#define D1S    39
#define E1F   D1S
#define E1     41
#define F1     44
#define F1S    46
#define G1F   F1S
#define G1     49
#define G1S    52
#define A1F   G1S
#define A1     55
#define A1S    58
#define B1F   A1S
#define B1     62
#define C2     65
#define C2S    69
#define D2F   C2S
#define D2     73
#define D2S    78
#define E2F   D2S
#define E2     82
#define F2     87
#define F2S    93
#define G2F   F2S
#define G2     98
#define G2S   104
#define A2F   G2S
#define A2    110
#define A2S   117
#define B2F   A2S
#define B2    123
#define C3    131
#define C3S   139
#define D3F   C3S
#define D3    147
#define D3S   156
#define E3F   D3S
#define E3    165
#define F3    175
#define F3S   185
#define G3F   F3S
#define G3    196
#define G3S   208
#define A3F   G3S
#define A3    220
#define A3S   233
#define B3F   A3S
#define B3    247
#define C4    262
#define C4S   277
#define D4F   C4S
#define D4    294
#define D4S   311
#define E4F   D4S
#define E4    330
#define F4    349
#define F4S   370
#define G4F   F4S
#define G4    392
#define G4S   412
#define A4F   G4S
#define A4    440
#define A4S   466
#define B4F   A4S
#define B4    494
#define C5    523
#define C5S   554
#define D5F   C5S
#define D5    587
#define D5S   622
#define E5F   D5S
#define E5    659
#define F5    698
#define F5S   740
#define G5F   F5S
#define G5    784
#define G5S   830
#define A5F   G5S
#define A5    880
#define A5S   932
#define B5F   A5S
#define B5    988
#define C6   1047
#define C6S  1109
#define D6F   C6S
#define D6   1175
#define D6S  1245
#define E6F   D6S
#define E6   1318
#define F6   1397
#define F6S  1480
#define G6F   F6S
#define G6   1568
#define G6S  1661
#define A6F   G6S
#define A6   1760
#define A6S  1865
#define B6F   A6S
#define B6   1976
#define C7   2093
#define C7S  2217
#define D7F   C7S
#define D7   2349
#define D7S  2489
#define E7F   D7S
#define E7   2637
#define F7   2794
#define F7S  2960
#define G7F   F7S
#define A7   3520
#define A7S  3729
#define B7F   A7S
#define B7   3951
#define C8   4186
#define C8S  4435
#define D8F   C8S
#define D8   4699
#define D8S  4978
#define E8F   D8S
#define E8   5274
#define F8   5588
#define F8S  5920
#define G8F   F8S
#define G8   6272
#define G8S  6645
#define A8   7040
#define A8S  7459
#define B8F   A8S
#define B8   7902


// Note macros for the lazy
#define WHOLE                1
#define HALF               0.5
#define QUARTER            0.25
#define EIGHTH           0.125
#define SIXTEENTH       0.0625
#define THIRTY_SECOND  0.03125
#define SIXTY_FOURTH  0.015625

/// Note-to-Milliseconds (at given tempo)
/// @param Note:
///   * Whole note is 1
///   * Half note is 0.5
///   * Quater note is 0.25
///   ...
///   * 1/(2^(Note))
/// @return:
///   An integer millisecond value
#define NTM(note, tempo) ((60000 / (double)tempo) * note) / 4

/// Same as NTM(note, tempo), except it uses pre-define variable/macro "TEMPO"
/// Saves you the trouble of passing tempo every time
#define NTM(note) (unsigned int)(((60000 / (double)TEMPO) * note) / 4)

/* Examples:
 *
 * #include <Windows.h>
 * ...
 * Beep(C5, NTM(WHOLE, 120));
 * Beep(D5, NTM(HALF, 120));
 * Beep(E5, NTM(QUARTER, 120));
 *
 * // OR //
 *
 * final int TEMPO = 120;
 * Beep(C5, NTM(WHOLE));
 * Beep(D5, NTM(HALF));
 * Beep(E5, NTM(QUARTER));
 *
 * // OR //
 *
 * final int TEMPO = 120;
 * Beep(C5, NTM(1));
 * Beep(D5, NTM(0.5));
 * Beep(E5, NTM(0.25));
 *
 * All provide same output
 */


#endif // AUDIO_HPP_INCLUDED
