#include<blocks.hpp>
#include <vector>
std::vector <block_entry> blockreg;
void register_block(int val,char havegrav,char havecoll,SDL_Rect tex){
    blockreg.insert(blockreg.begin()+val,{(unsigned char)(havegrav?1<<7:0|havecoll?1<<6:0),tex});

}
