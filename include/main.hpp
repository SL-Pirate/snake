#pragma once

//marcos
#define SDL_MAIN_HANDLED
#define VERSION "v4.1"
#define texWidth 16
#define texHeight 16
#define numFoodItems 3

//for debugging purposes only
#if defined(DEBUG_LINUX)
#define realP "/home/slpirate/Commons/programming/C++/snake/"
#elif defined(DEBUG_WIN)
#define realP "F:\\programming\\c++\\snake\\"
#else
#define realP ""
#endif

//for debugging purposes
#include <iostream>
#if defined (__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#elif defined (_WIN32)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif 
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <wx/wx.h>


//ENUMs
enum ID{WALL, SNAKE, FOOD};
//enums required to determine the direction of the movement of the snake
enum Dir{up, down, left, right};
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