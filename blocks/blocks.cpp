#include<blocks.hpp>
#include <vector>
std::vector <block_entry> blockreg;
void register_block(int val,char havegrav,char havecoll,char infjmp,SDL_Rect tex,const char* name,double cfriction,double cgrav,double refindex){
    blockreg.insert(blockreg.begin()+val,{(unsigned char)(havegrav?1<<7:0|havecoll?1<<6:0|infjmp?1<<5:0),tex,(char*)name,cfriction,cgrav,refindex});

}
