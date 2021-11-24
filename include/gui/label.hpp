#include <gui/guielement.hpp>
#include <vector>

class label:public guielement{
    void tick();
    label(const char* text);
    private:
        const char* text;

};
