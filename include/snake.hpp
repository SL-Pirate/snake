#pragma once

#include "main.hpp"
#include "sdl_window.hpp"
#include "graphic_handler.hpp"

enum Dir{up, down, left, right};

class Entity{
    protected:
    Window *gameWin = nullptr;
    SDL_Texture *texture = nullptr;
    //GraphicItem *arr[rows][cols];
    GraphicItem ***arr;
    
    public:
    Entity();
};


class Snake : public Entity {
    GraphicItem *snake[rows*cols];
    int length = 0;
    Dir dir = right;
    
    public:
    Snake(Window *gameWin, GraphicItem ***arr);
    void addToArr();
    void move();
    void move(Dir direction);
};


class Wall : public Entity {
    public:
    int c = 0;
    Wall(Window *gameWin, GraphicItem ***arr);
};