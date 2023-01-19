# Snake game in sdl, my own version

## build dependancies

SDL2

SDL2_image

SDL2_ttf

## compiling for linux

`mkdir build/linux`

`cp lib/linux/* build/linux/`

`g++ src/* -o build/linux/snake -Iinclude/ -lSDL2 -lSDL2_image -lSDL2_ttf -O3`