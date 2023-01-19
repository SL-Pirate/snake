#pragma once

#include "main.hpp"
#include "sdl_window.hpp"
#include "graphic_handler.hpp"


//enums required to determine the direction of the movement of the snake
//"stop" is only a placeholder
enum Dir{up, down, left, right, stop};


//parent class for all entities snake, wall and food
class Entity{
    protected:
    Window *gameWin = nullptr;
    SDL_Texture *texture = nullptr;
    //GraphicItem *arr[rows][cols];
    GraphicItem ***arr;
    //used for passing food entities to set them to null so food can be regenerated if eaten
    GraphicItem *item = nullptr;
    
    public:
    Entity();
    ~Entity();

    //used for passing food entities to set them to null so food can be regenerated if eaten
    virtual void clearItem() = 0;

    //just to make this class abstract
    //virtual void placeholderFunc();
};


//definition of the class Snake, child of entity
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


//definition of the class Wall, child of entity 
class Wall : public Entity {
    void clearItem();
    public:
    Wall(Window *gameWin, GraphicItem ***arr);
};


//definition of the class Food, child of entity
class Food : public Entity {
    int cords[2];
    void genCords();

    public:
    Food(Window *gameWin, GraphicItem ***arr);


    void genFood();
    void clearItem();
};