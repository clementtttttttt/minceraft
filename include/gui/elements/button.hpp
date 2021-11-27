#include <gui/guielement.hpp>
#include <vector>

class button:public guielement{
    public:
        void tick();
        button(const char* text,u32 x,u32 y,u32 szx,u32 szy);
    private:
        const char* text;
        u32 szx,szy;

};
