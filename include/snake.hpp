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
    //used for passing food entities
    GraphicItem *item = nullptr;
    
    public:
    Entity();

    //used for passing food entities
    virtual void clearItem() = 0;

    //just to make this class abstract
    //virtual void placeholderFunc();
};


class Snake : public Entity {
    GraphicItem *snake[rows*cols];
    int length = 0;
    Dir dir = right;
    int score = 0;

    void ate(GraphicItem *nextItem);
    void clearItem();
    
    public:
    Snake(Window *gameWin, GraphicItem ***arr);
    void addToArr();
    bool move();
    bool move(Dir direction);
};


class Wall : public Entity {
    void clearItem();
    public:
    Wall(Window *gameWin, GraphicItem ***arr);
};


class Food : public Entity {
    int cords[2];
    void genCords();

    public:
    Food(Window *gameWin, GraphicItem ***arr);
    void genFood();
    
    void clearItem();
};