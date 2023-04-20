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
    Food **foods = nullptr;
    Wall *wall = nullptr;
    cMain *parent = nullptr;
    int penaltyPerCentForGameQuitOnMultiPlayer = 10;
    BodyColor *culpritSnake = nullptr;

    void setDir(Dir currentDir, Dir *dirs);
    void setDir(Dir currentDir, Dir *dirs, bool *snake_moved);
    Dir *resetDirs();

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