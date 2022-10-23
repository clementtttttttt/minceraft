#include <api.hpp>
#include <types.hpp>
#include <utils.hpp>


#if defined(__MINGW32__) || defined(__linux__)


typedef struct{
    SDL_Renderer *renderer;
    SDL_Window *window;

} app;



#include <SDL.h>
#include <SDL_image.h>
#define SDL_MAIN_HANDLED

void *tex, *mob, *font;

void sysspec_delay(double d){
    SDL_Delay(d);
}

#include <iostream>
app mainapp;
void     sysspec_clearscrn(){
    SDL_RenderClear(mainapp.renderer);
}
void    sysspec_updatescrn(){
    SDL_RenderPresent(mainapp.renderer);
}

int sysspec_getmousepos(int *x, int *y){

    return SDL_GetMouseState(x,y);
}

void sysspec_setcolourmod(void* tex,u8 r,u8 g,u8 b){
    SDL_SetTextureColorMod((SDL_Texture*)tex,r,g,b);
}

void blit(SDL_Texture *texture, SDL_Rect *clip, SDL_Rect *dest) {

  SDL_RendererFlip flip = (clip->w < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_Rect b;
  memcpy(&b, clip, sizeof(b));
  clip->w = abs(clip->w);

  SDL_RenderCopyEx(mainapp.renderer, texture, clip, dest, (double)NULL,
                   (SDL_Point *)NULL, flip);
  memcpy(clip, &b, sizeof(b));
}


void sysspec_putimg(void* tex, rect *src, rect *des){
    blit((SDL_Texture*)tex,(SDL_Rect*)src,(SDL_Rect*)des);
}

void sysspec_getscreensz(int* x,int* y){
  SDL_GetRendererOutputSize(mainapp.renderer, x, y);

}
unsigned char * sysspec_getkeystate(){
    return (u8*) SDL_GetKeyboardState(NULL);
}

void sysspec_settextrans(void* tex, u8 alpha){
    SDL_SetTextureAlphaMod((SDL_Texture*)tex,alpha);
}

void *sysspec_loadtex(std::string file) {
  SDL_Texture *texture;
  texture = IMG_LoadTexture(mainapp.renderer, file.c_str());
  if (!texture) {
    std::cout << "TEXTURE LOAD ERROR: " << file << std::endl;
  } else
    std::cout << "TEXTURE LOADED SUCCESSFULLY:" << file << std::endl;
  return texture;
}
SDL_Event e;
int sysspec_poll(){
    return SDL_PollEvent(&e);
}

void sysspec_checkquit(){
    if(e.type==SDL_QUIT){
        exit(0);
    }
}

void sysspec_init(){
#ifdef __SIZEOF_INT128__
  *((unsigned __int128 *)&mainapp) = 0;
#endif
  SDL_Rect a1;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    std::cout << "SDL_Init() ERROR" << std::endl;
    exit(1);
  }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        exit(1);
    }

  mainapp.window =
      SDL_CreateWindow("Minceraft", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, screensz_x, screensz_y, 0);
  if (!(mainapp.window)) {
    std::cout << "SDL_CreateWindow ERROR" << std::endl;
    exit(1);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  SDL_SetHint(SDL_HINT_RENDER_VSYNC,"0");
  mainapp.renderer =
      SDL_CreateRenderer(mainapp.window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(mainapp.renderer, 0x87, 0xce, 0xeb, 255);
  SDL_RenderSetLogicalSize(mainapp.renderer, screensz_x, screensz_y);
  SDL_RenderClear(mainapp.renderer);

  if (!mainapp.renderer) {
    printf("SDL_CreateRenderer FAIL, ERROR=%ld \n", (unsigned long long)SDL_GetError());
    exit(1);
  }

    mob = sysspec_loadtex("gametex/mobs.png");
  tex = sysspec_loadtex("gametex/blocks.png");
  font = sysspec_loadtex("gametex/font.png");

}
void sysspec_putfont(char in,u32 x,u32 y,float xscale,float yscale){
    if(in=='p'||in=='q'||in=='g'||in=='y'){
          y+=28*yscale;
    }
    SDL_Rect rec{(int) x,(int) y,(int)((float)32*xscale),(int)((float)64*yscale)};
    int xindex,yindex;
    if(in>='A'&&in<='Z'){
        xindex=((in-'A')%12)*8;
        yindex=((in-'A')/12)*16;
    }
    if(in>='a'&&in<='z'){
        xindex=((in-'a'+2)%12)*8;
        yindex=((in-'a'+2)/12+2)*16;

    }
    if(in>='0'&&in<='9'){
        xindex=((in-'0'+4)%12)*8;
        yindex=((in-'0'+4)/12+4)*16;
    }
    if(in=='&'){
        xindex=56;
        yindex=80;
    }
    SDL_Rect texrec{(int) xindex,(int) yindex,(int)8,(int)16};
    if(in!=' '&&in!='\n')
      blit((SDL_Texture*)font, &texrec, &rec);

}


void sysspec_prints(u32 x,u32 y,float xscale,float yscale,const char* format, ...){
  char buf[1024];
  va_list args;
  va_start (args, format);
  vsprintf(buf,format,args);
  char* s=&buf[0];
  u32 c=0,yc=0;
  while(*s){

    sysspec_putfont(*s,x+c*(32*xscale)+c*4*xscale,y+yc*(yscale*64),xscale,yscale);
    if(*s=='\n'){
        c=0;
        ++yc;
    }else{
        ++c;
    }
    ++s;
  }
    va_end(args);

}

void sysspec_prints(u32 x,u32 y,const char* format, ...){
  char buf[1024];
  va_list args;
  va_start (args, format);
  vsprintf(buf,format,args);
  char* s=&buf[0];
  u32 c=0,yc=0;
  while(*s){

    sysspec_putfont(*s,x+c*32+c*4,y+yc*64,1,1);
    if(*s=='\n'){
        c=0;
        ++yc;
    }else{
        ++c;
    }
    ++s;
  }
    va_end(args);

}
#endif
