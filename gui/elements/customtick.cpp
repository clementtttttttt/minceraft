#include <utils.hpp>
#include "gui/elements/customtick.hpp"


customtick::customtick(void(*han)()){
    this->han=han;

}
void customtick::tick(){
    this->han();
}
