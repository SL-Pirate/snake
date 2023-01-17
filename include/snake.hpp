#pragma once

#include "main.hpp"
#include "sdl_window.hpp"
#include "graphic_handler.hpp"

enum Dir{up, down, left, right, stop};

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
    bool addToArr();
    bool move();
    bool move(Dir direction);
};


class Wall : public Entity {
    public:
    Wall(Window *gameWin, GraphicItem ***arr);
};


class Food : public Entity {
    int cords[2];
    void genCords();

    public:
    Food(Window *gameWin, GraphicItem ***arr);
    void genFood();
    void refresh();
};