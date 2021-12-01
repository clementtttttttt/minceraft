#include <gui/guielement.hpp>
#include <vector>

class customtick:public guielement{
    public:
        void tick();
        customtick(void(*han)());

    private:
        void(*han)();

};
