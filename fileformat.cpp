
#include "fileformat.hpp"
#include "world.hpp"
#include <iostream>
#include <cstring>
extern int world_time;
//each yrow start withs a unsigned long long that specifies the blocks in a y row
void save_world(char* filename){
    FILE * worldfile;
    struct minceraft_world_file currentworld;
    currentworld.magic=0xC3C56D696E636572;
    currentworld.magic2=0x6166746D61746521;
    currentworld.playerpos.x=entity_list[0]->getpos().x;
    currentworld.playerpos.y=entity_list[0]->getpos().y;
    currentworld.world_time=world_time;
    currentworld.wxsize=world.size();
    currentworld.worldstartx=-((long long)negworld.size()-1);/* pos world starts at 0  */
    currentworld.negworldsize=(long long)negworld.size();
    worldfile=fopen(filename,"wb");
    fwrite(&currentworld,sizeof(minceraft_world_file),1,worldfile);
    for(long long x=currentworld.worldstartx;x<(long long)currentworld.wxsize;++x){

        std::vector<std::vector<block>> *world_ref = x>=0?&world:&negworld;
        unsigned long long ysz=(*world_ref)[abs(x)].size();
        fwrite(&ysz,8,1,worldfile);
        for(unsigned long long y=0;y<ysz;++y){
            block b = getBlock(x,y);
            fwrite(&b,sizeof(struct block),1,worldfile);
        }


    }
    fclose(worldfile);
}

int off;

int load_world(std::string_view buf){
    std::cout << "LOADING WORLD " << std::endl;
    FILE * worldfile;
    u64 test_magic;
    struct minceraft_world_file currentworld;

    memcpy(&currentworld,buf.data(),std::min(sizeof(minceraft_world_file),buf.size()));
    /*
    u64 magic=0xC3C56D696E636572;
    u64 magic2=0x6166746D61746521;*/
    if(currentworld.magic!=0xC3C56D696E636572&&currentworld.magic2!=0x6166746D61746521){
        std::cout << "Wrong magic " << currentworld.magic << " " << currentworld.magic2 <<std::endl;
        return 1;
    }
    off += sizeof(minceraft_world_file);
    negworld.resize(currentworld.negworldsize);
    world.resize(currentworld.wxsize);
   // struct block test;
    for(long long x=currentworld.worldstartx;x<(long long)currentworld.wxsize;++x){

        std::vector<std::vector<block>> *world_ref = x>=0?&world:&negworld;
        unsigned long long ysz;
        memcpy(&ysz,buf.data()+off,8);

        (*world_ref)[abs(x)].resize(ysz);
        for(unsigned long long y=0;y<ysz;++y){
            fread(&(*world_ref)[abs(x)][y],sizeof(struct block),1,worldfile);
        }


    }
    world_time=currentworld.world_time;
    entity_list[0]->setloc(currentworld.playerpos.x,currentworld.playerpos.y);
    return 0;
}

int load_world(char* filename){
    std::cout << "LOADING WORLD " << filename << std::endl;
    FILE * worldfile;
    u64 test_magic;
    struct minceraft_world_file currentworld;


    worldfile=fopen(filename,"rb");
    if(worldfile==NULL){
        std::cout << "Failed to open world file" << std::endl;
        return 2;
    }
    fread(&currentworld,sizeof(minceraft_world_file),1,worldfile);
    /*
    u64 magic=0xC3C56D696E636572;
    u64 magic2=0x6166746D61746521;*/
    if(currentworld.magic!=0xC3C56D696E636572&&currentworld.magic2!=0x6166746D61746521){
        std::cout << "Wrong magic " << currentworld.magic << " " << currentworld.magic2 <<std::endl;
        return 1;
    }
    negworld.resize(currentworld.negworldsize);
    world.resize(currentworld.wxsize);
   // struct block test;
    for(long long x=currentworld.worldstartx;x<(long long)currentworld.wxsize;++x){

        std::vector<std::vector<block>> *world_ref = x>=0?&world:&negworld;
        unsigned long long ysz;
        fread(&ysz,8,1,worldfile);

        (*world_ref)[abs(x)].resize(ysz);
        for(unsigned long long y=0;y<ysz;++y){
            fread(&(*world_ref)[abs(x)][y],sizeof(struct block),1,worldfile);
        }


    }
    world_time=currentworld.world_time;
    entity_list[0]->setloc(currentworld.playerpos.x,currentworld.playerpos.y);
    fclose(worldfile);
    return 0;
}
