#include <gui/guielement.hpp>
#include <vector>

class image:public guielement{
    public:
        void tick();
        image(const char* path,u32 x,u32 y,u32 xs,u32 ys,u32 ixs,u32 iys,u8 transparency);
    private:
        SDL_Texture* i;
        const char* path;
        u32 xs,ys,ixs,iys;
        u8 transparency;
        bool init=false;

};
