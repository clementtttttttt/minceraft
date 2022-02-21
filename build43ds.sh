$DEVKITARM/bin/arm-none-eabi-gcc *.cpp *.c -I include/ -I /usr/x86_64-w64-mingw32/include/SDL2  -l:libpthread.a src/*.cpp entity/*.cpp gui/*.cpp blocks/*.cpp gui/elements/*.cpp -lSDL2_image -lSDL2 -lcomdlg32 -lole32 -static-libgcc -static-libstdc++ -o win_run/minceraft.exe -I $DEVKITPRO/portlibs/3ds/include/SDL -Ofast -Wl,--stack,16777216  

