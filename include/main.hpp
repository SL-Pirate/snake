#pragma once

//marcos
#define SDL_MAIN_HANDLED
#define VERSION "v2.0"
#define winWidth 496
#define winHeight 496
#define texWidth 16
#define texHeight 16
#define ROWS winHeight / 16 //resolves to number y
#define COLS winWidth / 16 //resolves to number x
#define numFoodItems 3

#if defined(DEBUG)
#define realP "/home/slpirate/Commons/programming/C++/snake/"
#elif defined(DEBUG_LINUX)
#define realP "F:\\programming\\c++\\snake\\"
#else
#define realP ""
#endif


//for debugging purposes
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <wx/wx.h>


//globals vars
enum ID{WALL, SNAKE, FOOD};
//enums required to determine the direction of the movement of the snake
//"stop" is only a placeholder
enum Dir{up, down, left, right, stop};