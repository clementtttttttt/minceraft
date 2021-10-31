#include<blocks.hpp>
#include <vector>
std::vector <block_entry> blockreg;
void register_block(int val,char havegrav,char havecoll,char infjmp,SDL_Rect tex,char* name,double cfriction,double cgrav){
    blockreg.insert(blockreg.begin()+val,{(unsigned char)(havegrav?1<<7:0|havecoll?1<<6:0|infjmp?1<<5:0),tex,name,cfriction,cgrav});

}
