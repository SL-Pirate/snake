#pragma once

#include "main.hpp"
#include "graphic_handler.hpp"
#include "sound.hpp"
#include "sdl_window.hpp"

#include <wx/wx.h>
#include <array>
#include <SDL_ttf.h>
#include <random>

//parent class for all entities snake, wall and food
class Entity {
protected:
    Window *gameWin = nullptr;
    SDL_Texture *texture = nullptr;
    //GraphicItem *arr[ROWS()][COLS()];
    GraphicItem ***arr = nullptr;
    //used for passing food entities to set them to null so food can be regenerated if eaten
    GraphicItem *item = nullptr;

public:
    Entity();

    virtual ~Entity();

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
    Fonts(Window *gameWin, const std::string &title, BodyColor color, int x, int y);

    ~Fonts() override;

    void setTitle(const std::string &pTitle);

    void clearItem() override;

    [[nodiscard]] GraphicItem *getItem() const;
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
    Sound *eatSound;
    Sound *dieSound;

    void ate(GraphicItem *nextItem);

    Dir getNextDir() const;

public:
    Snake(Window *gameWin, GraphicItem ***arr, wxSlider *difficulty, BodyColor color);

    ~Snake() override;

    void clearItem() override;

    void addToArr() const;

    bool move();

    bool move(Dir *dirs);

    void setInitialDir(Dir pDir) const;

    int getScore() const;

    void applyPenalty(double penaltyPerCent);

    Fonts *font = nullptr;
    BodyColor color;
};


//definition of the class Wall, child of entity 
class Wall : public Entity {
public:
    Wall(Window *gameWin, GraphicItem ***arr);

    void clearItem() override;
};


//definition of the class Food, child of entity
class Food : public Entity {
    static std::mt19937 gen;
    std::array<int, 2> cords = {};

public:
    Food(Window *gameWin, GraphicItem ***arr);

    void genFood();

    void clearItem() override;

};
