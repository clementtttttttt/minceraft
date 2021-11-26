#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <utils.hpp>

label title_minceraft("Minceraft",screensz_x/2-(144)-(18),60+((screensz_y-640)/640)*640);

guielement* title[]={
    &title_minceraft,(guielement*) 0

};
