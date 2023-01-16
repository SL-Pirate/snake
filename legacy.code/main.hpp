#pragma once

#include <iostream>
#include <thread>
#include <chrono>

#ifdef __linux__
#include <curses.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

const int width = 60;
const int height = 20;

const char wall = '#';
const char body = '@';
const char food = '$';
const char space = ' ';

class Display{
    public:
//    Display();

    char screen[height][width];

    //only draws what's in the display array
    void draw(); 
    void drawWall();
};

class Body{
    static const int maxLength = 100;

    public:
    Display *display;
    enum Dir{up, down, left, right};
    //v = vertical and h = horizontal
    enum VorH{v = 0, h = 1};
    int length = 2;
    //snake[unit (where 0 is the head)][cordinate (where v (as in vertical) or 0 is y and h (as in horizontal) or 1 is x)]
    int snake[maxLength][2]; 
    Dir direction;

    Body(Display *display);

    void addToDisplay();
    void moveSnake();
};

void draw(Display *display);

void mainloop(Body *body);
void keyboardInput(Body *body);