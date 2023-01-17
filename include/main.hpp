#pragma once

//for debugging purposes
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include <chrono>

//marcos
#define winWidth 608
#define winHeight 608
#define texWidth 16
#define texHeight 16
#define rows 608 / 16 //resolves to number y
#define cols 608 / 16 //resolves to number x