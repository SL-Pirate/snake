#pragma once

#include "entity.hpp"
#include "main.hpp"
#include "wxwids.hpp"
#include "sdl_window.hpp"

class Window;
class GraphicItem;
class Wall;
class Snake;
class Food;

typedef std::vector<std::unique_ptr<Food> > FoodContainer;

// defining class Game
class Game {
    Window *gameWin = nullptr;
    SDL_Texture *background = nullptr;
    Arena arr;
    bool isKeyPressed = false;
    bool isPaused = false;
    std::unique_ptr<FoodContainer> foodContainer = nullptr;
    std::unique_ptr<Wall> wall = nullptr;
    cMain *parent = nullptr;
    int penaltyPerCentForGameQuitOnMultiPlayer = 10;
    BodyColor *culpritSnake = nullptr;

    static void setDir(Dir currentDir, Dir *dirs);

    static void setDir(Dir currentDir, Dir *dirs, bool *snake_moved);

    static Dir *resetDirs();

    void singlePlayerEventHandler(wxTimerEvent &event);

    void multiPlayerEventHandler(wxTimerEvent &event);

    void stopGame(bool isMultiplayer) const;

public:
    Game(cMain *parent, Window *gameWin);

    ~Game();

    void startSingleplayer();

    void startMultiplayer();

    void resume();

    std::unique_ptr<Snake> snake = nullptr;
    std::unique_ptr<Snake> snake1 = nullptr;
    std::unique_ptr<Snake> snake2 = nullptr;
};
