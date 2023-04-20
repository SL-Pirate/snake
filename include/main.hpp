#pragma once

//marcos
#define SDL_MAIN_HANDLED
#define VERSION "v5.0"
#define texWidth 16
#define texHeight 16
#define numFoodItemsSinglePlayer 2
#define numFoodItemsMultiPlayer 3
#define maxNumChainedMovesAllowed 3

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
enum Dir{up, down, left, right, none};
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