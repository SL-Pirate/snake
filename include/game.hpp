#pragma once

#include "main.hpp"
#include "wxwids.hpp"
#include "sdl_window.hpp"

class Window;
class GraphicItem;
class Wall;
class Snake;
class Food;

// defining class Game
class Game {
    Window *gameWin = nullptr;
    SDL_Texture *background = nullptr;
    GraphicItem ***arr = nullptr;
    bool isKeyPressed = false;
    bool isPaused = false;
    Food **foods = nullptr;
    Wall *wall = nullptr;
    cMain *parent = nullptr;
    int penaltyPerCentForGameQuitOnMultiPlayer = 10;
    BodyColor *culpritSnake = nullptr;

    static void setDir(Dir currentDir, Dir *dirs);

    static void setDir(Dir currentDir, Dir *dirs, bool *snake_moved);

    static Dir *resetDirs();

    void singlePlayerEventHandler(wxTimerEvent &event);

    void multiPlayerEventHandler(wxTimerEvent &event);

    void stopGame(bool isMultiplayer);

public:
    Game(cMain *parent, Window *gameWin);

    ~Game();

    void startSingleplayer();

    void startMultiplayer();

    void resume();

    Snake *snake = nullptr;
    Snake *snake1 = nullptr;
    Snake *snake2 = nullptr;
};
