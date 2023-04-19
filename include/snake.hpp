#pragma once

#include "main.hpp"
#include "sdl_window.hpp"
#include "graphic_handler.hpp"
#include "sound.hpp"


//parent class for all entities snake, wall and food
class Entity{
    protected:
    Window *gameWin = nullptr;
    SDL_Texture *texture = nullptr;
    //GraphicItem *arr[ROWS()][COLS()];
    GraphicItem ***arr = nullptr;
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


//definition of the class Fonts, child of entity
class Fonts : public Entity {
    TTF_Font *font = nullptr;
    SDL_Rect *dst = nullptr;
    std::string title;
    BodyColor color;

    public:
    //int x = horizontal position of the label
    //int y = vertical position of the label
    Fonts(Window *gameWin, std::string title, BodyColor color, int x, int y);
    ~Fonts();
    
    void setTitle(std::string title);
    void clearItem();
    GraphicItem *getItem();
};


//definition of the class Snake, child of entity
class Snake : public Entity {
    // const int size = ROWS() * COLS();
    GraphicItem **snake;
    int length = 0;
    Dir dir = right;
    Dir *registeredDirs;
    int score = 0;
    wxSlider *difficulty = nullptr;
    std::string scoreTitle;
    Sound* eatSound;
    Sound* dieSound;

    void ate(GraphicItem *nextItem);
    void clearItem();
    Dir getNextDir();
    
    public:
    Snake(Window *gameWin, GraphicItem ***arr, wxSlider *difficulty, BodyColor color);
    ~Snake();

    void addToArr();
    bool move();
    bool move(Dir *dirs);
    void setInitialDir(Dir dir);
    int getScore();
    void applyPenalty(double penaltyPerCent);
    void applyPenalty();

    Fonts *font = nullptr;
    BodyColor color;
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