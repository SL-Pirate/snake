#pragma once

//for debugging purposes
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <chrono>
#include <random>
#include <time.h>

//marcos
#define winWidth 496
#define winHeight 496
#define texWidth 16
#define texHeight 16
#define rows winHeight / 16 //resolves to number y
#define cols winWidth / 16 //resolves to number x

#ifdef DEBUG
#define realP "/home/slpirate/Commons/programming/C++/snake/"
#else
#define realP ""
#endif

//globals vars
enum ID{WALL, SNAKE, FOOD};
