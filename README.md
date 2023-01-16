## Snake game in sdl, my own version

# build dependancies

SDL2

SDL2_image

# compiling for linux

`mkdir build/linux`

`cp lib/linux/* build/linux/`

`g++ src/* -o build/linux/snake -Iinclude/ -lSDL2 -lSDL2_image -O3`