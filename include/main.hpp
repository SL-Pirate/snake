#pragma once

//marcos
#define SDL_MAIN_HANDLED
#define VERSION "v3.0"
//#define multiWinWidth 592
//#define multiWinWidth 592
#define texWidth 16
#define texHeight 16
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
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <wx/wx.h>


//ENUMs
enum ID{WALL, SNAKE, FOOD};
//enums required to determine the direction of the movement of the snake
//"stop" is only a placeholder
enum Dir{up, down, left, right, stop};
enum BodyColor{RED, BLUE};

//global vars
inline int winWidth = 496;
inline int winHeight = 496;
//resolves to y
inline const int ROWS(){
    return winHeight / 16;
}
//resolves to x
inline const int COLS(){
    return winWidth / 16;
}