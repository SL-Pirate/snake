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
    Food *foods[numFoodItems];
    Wall *wall = nullptr;
    cMain *parent = nullptr;

    public:
    Game(cMain *parent);
    ~Game();

    void start();
    void startMultiplayer();
    void resume();

    Snake *snake = nullptr;
    Snake *snake1 = nullptr;
    Snake *snake2 = nullptr;
};