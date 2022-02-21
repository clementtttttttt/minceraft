#include "types.hpp"



struct minceraft_world_file{
    u64 magic;
    u64 magic2;
    unsigned long long wxsize;
    vec2 playerpos;
    int world_time;
    long long worldstartx;
    unsigned long long negworldsize;
}__attribute__((packed));
int load_world(char* filename);
void save_world(char* filename);
