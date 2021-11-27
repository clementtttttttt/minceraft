#include <gui/title.hpp>
#include <gui/elements/label.hpp>
#include <gui/elements/button.hpp>
#include <utils.hpp>

#define calccentrepos(strlength) screensz_x/2-(strlength/2*32)-(strlength/2*4)
#define calctoppos(pos) pos+((screensz_y-640)/640)*640

label title_minceraft("Minceraft",screensz_x/2-(144)-(18),calctoppos(60));
button play_button("Play",calccentrepos(4),calctoppos(200),32*4,64);

guielement* title[]={
    &title_minceraft,&play_button,(guielement*) 0

};
