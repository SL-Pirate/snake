# Snake game in sdl, my own version

## build dependancies

SDL2

SDL2_image

SDL2_ttf

## compiling for linux

`mkdir build/linux`

`cp res build/linux/`

`g++ src/* -o build/linux/snake -Iinclude/ -lSDL2 -lSDL2_image -lSDL2_ttf -O3 `wx-config --libs` `wx-config --cxxflags``

## conpiling for windows

`mkdir build\windows`

`cp res build/windows`

add icon `windres .\res\icon.rc -O coff -o res\icon.res`

compile `g++ src\*.cpp -o build\windows\snake.exe -L {Location where SDL2 libraries are saved}\lib -lmingw32 -lSDL2 -lSDL2_image -lSDL2_ttf -Iinclude\ -I{Location where SDL2 libraries are saved}\include -O3`

Example for compiler command: `g++ src\*.cpp -o build\windows\snake.exe -L D:\lib\SDL2\lib -lmingw32 -lSDL2 -lSDL2_image -lSDL2_ttf -Iinclude\ -ID:\lib\SDL2\include -O3`