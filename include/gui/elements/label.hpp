#include <gui/guielement.hpp>
#include <vector>

class label:public guielement{
    public:
        void tick();
        label(const char* text,u32 x,u32 y);
        label(const char* text,u32 x,u32 y,float xsc,float ysc);

    private:
        const char* text;
        float xsc,ysc;

};
