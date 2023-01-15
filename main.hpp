#pragma once

#include <iostream>

const int width = 60;
const int height = 20;

const char wall = '#';
const char body = '@';
const char food = '$';
const char space = ' ';

class Display{
    public:
    char screen[height][width];

    void draw();
};

void draw(Display *display);