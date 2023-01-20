#pragma once

#include "main.hpp"
#include "wxwids.hpp"

class Window;
class GraphicItem;
class Wall;
class Snake;
class Food;

//defining class Game
class Game{
    private:
    Window *gameWin = nullptr;
    SDL_Texture *background = nullptr;
    GraphicItem ***arr = nullptr;
    bool gameRunning = true;
    bool isKeyPressed = false;
    bool isPaused = false;
    SDL_Event evnt;
    Dir dir;
    Food *foods[numFoodItems];
    Wall *wall = nullptr;
    Snake *snake = nullptr;

    public:
    Game(cMain *parent);
    ~Game();

    void resume();
};