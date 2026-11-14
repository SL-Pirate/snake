#include "game.hpp"

#include <SDL_image.h>
#include <thread>
#include <wx/wx.h>

#include "sdl_window.hpp"
#include "entity.hpp"
#include "error.hpp"
#include "sound.hpp"

Game::Game(cMain *parent, Window *gameWin) {
    this->parent = parent;
    this->gameWin = gameWin;
    // IMG_Init returns the same number that is passed
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        throw ImageInitError();
    }
    if (TTF_Init() != 0) {
        throw TTF_InitError();
    };
    if (Mix_Init(MIX_INIT_MP3) == 0 || Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        Sound::hasSound = false;
    } else {
        Sound::hasSound = true;
    }
}

void Game::startSingleplayer() {
    background = gameWin->loadTexture(openRes("gfx/grass-pattern.png")); // res/gfx/grass-pattern.png
    foodContainer = std::make_unique<FoodContainer>(NUM_FOOD_ITEMS_SINGLE_PLAYER);

    // arr[ROWS()][COLS()]
    // equates to arr[y][x]
    arr = Arena(ROWS());
    for (int i = 0; i < ROWS(); i++) {
        arr[i] = std::vector<std::shared_ptr<GraphicItem> >(COLS());
    }

    for (int i = 0; i < ROWS(); i++) {
        for (int j = 0; j < COLS(); j++) {
            arr[i][j] = nullptr;
        }
    }

    wall = std::make_unique<Wall>(gameWin, &arr);

    // implementing snake & food
    snake = std::make_unique<Snake>(gameWin, &arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, RED);
    for (int i = 0; i < NUM_FOOD_ITEMS_SINGLE_PLAYER; i++) {
        (*foodContainer)[i] = std::make_unique<Food>(gameWin, &arr);
    }

    parent->m_timer.Bind(wxEVT_TIMER, &Game::singlePlayerEventHandler, this);
    parent->m_timer.Start(1000 / parent->difficulty->GetValue());
}

void Game::singlePlayerEventHandler(wxTimerEvent &) {
    Moves dirs = resetDirs();
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        if (evnt.type == SDL_QUIT) {
            stopGame(false);
        } else if (evnt.type == SDL_KEYDOWN) {
            switch (evnt.key.keysym.sym) {
                case SDLK_UP:
                    isKeyPressed = true;
                    setDir(up, dirs);
                    break;
                case SDLK_DOWN:
                    isKeyPressed = true;
                    setDir(down, dirs);
                    break;
                case SDLK_LEFT:
                    isKeyPressed = true;
                    setDir(left, dirs);
                    break;
                case SDLK_RIGHT:
                    isKeyPressed = true;
                    setDir(right, dirs);
                    break;
                case SDLK_ESCAPE:
                    isKeyPressed = true;
                    isPaused = true;
                    parent->pause();
                    break;
                case SDLK_q:
                    stopGame(false);
                default: ;
            }
        }
    }

    gameWin->clearRen();

    bool canKeepGoing = true;
    // move the snake
    if (isKeyPressed) {
        if (!isPaused) {
            canKeepGoing = snake->move(dirs);
            dirs = resetDirs();
            isKeyPressed = false;
        }
    } else {
        canKeepGoing = snake->move();
    }

    // refresh food
    try {
        for (int i = 0; i < NUM_FOOD_ITEMS_SINGLE_PLAYER; i++) {
            (*foodContainer)[i]->genFood();
        }
    } catch (GridSpaceFullError &) {
        canKeepGoing = false;
    }

    // displaying everything on screen
    gameWin->render(background);
    gameWin->render(snake->font->getItem());
    for (int i = 0; i < ROWS(); i++) {
        for (int j = 0; j < COLS(); j++) {
            if (arr[i][j] != nullptr) {
                gameWin->render(arr[i][j]);
            }
        }
    }

    if (!canKeepGoing) {
        stopGame(false);
    }
    gameWin->display();
}

void Game::startMultiplayer() {
    background = gameWin->loadTexture(openRes("gfx/grass-pattern.png")); // res/gfx/grass-pattern.png
    foodContainer = std::make_unique<FoodContainer>(NUM_FOOD_ITEMS_MULTIPLAYER);

    // arr[ROWS()][COLS()]
    // equates to arr[y][x]
    arr = Arena(ROWS());
    for (int i = 0; i < ROWS(); i++) {
        arr[i] = std::vector<std::shared_ptr<GraphicItem> >(COLS());
    }

    for (int i = 0; i < ROWS(); i++) {
        for (int j = 0; j < COLS(); j++) {
            arr[i][j] = nullptr;
        }
    }

    wall = std::make_unique<Wall>(gameWin, &arr);

    // implementing snake & food
    snake1 = std::make_unique<Snake>(gameWin, &arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, RED);
    snake2 = std::make_unique<Snake>(gameWin, &arr, parent->difficulty /*1000/parent->difficulty->GetValue()*/, BLUE);
    snake2->setInitialDir(left);
    for (int i = 0; i < NUM_FOOD_ITEMS_MULTIPLAYER; i++) {
        (*foodContainer)[i] = std::make_unique<Food>(gameWin, &arr);
    }

    parent->m_timer.Bind(wxEVT_TIMER, &Game::multiPlayerEventHandler, this);
    parent->m_timer.Start(1000 / parent->difficulty->GetValue());
}

void Game::multiPlayerEventHandler(wxTimerEvent &event) {
    Moves dir1 = resetDirs();
    Moves dir2 = resetDirs();

    const auto snake1_moved = std::make_shared<bool>(false);
    const auto snake2_moved = std::make_shared<bool>(false);
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        if (evnt.type == SDL_QUIT) {
            stopGame(true);
        } else if (evnt.type == SDL_KEYDOWN) {
            switch (evnt.key.keysym.sym) {
                case SDLK_UP:
                    isKeyPressed = true;
                    setDir(up, dir1, snake1_moved);
                    break;
                case SDLK_DOWN:
                    isKeyPressed = true;
                    setDir(down, dir1, snake1_moved);
                    break;
                case SDLK_LEFT:
                    isKeyPressed = true;
                    setDir(left, dir1, snake1_moved);
                    break;
                case SDLK_RIGHT:
                    isKeyPressed = true;
                    setDir(right, dir1, snake1_moved);
                    break;
                case SDLK_w:
                    isKeyPressed = true;
                    setDir(up, dir2, snake2_moved);
                    break;
                case SDLK_s:
                    isKeyPressed = true;
                    setDir(down, dir2, snake2_moved);
                    break;
                case SDLK_a:
                    isKeyPressed = true;
                    setDir(left, dir2, snake2_moved);
                    break;
                case SDLK_d:
                    isKeyPressed = true;
                    setDir(right, dir2, snake2_moved);
                    break;
                case SDLK_ESCAPE:
                    isKeyPressed = true;
                    isPaused = true;
                    parent->pause();
                    break;
                case SDLK_q:
                    stopGame(true);
                default: ;
            }
        }
    }

    gameWin->clearRen();

    // move the snake
    bool canKeepGoing = true;
    if (isKeyPressed) {
        if (!isPaused) {
            if (*snake1_moved) {
                canKeepGoing = snake1->move(dir1);
                *snake1_moved = false;
                dir1 = resetDirs();
            }

            if (*snake2_moved) {
                canKeepGoing = snake2->move(dir2);
                *snake2_moved = false;
                dir2 = resetDirs();
            }
            isKeyPressed = false;
        }
    } else {
        if (!snake1->move()) {
            snake1->applyPenalty(penaltyPerCentForGameQuitOnMultiPlayer);
            culpritSnake = std::make_shared<BodyColor>(snake1->color);
            canKeepGoing = false;
        }
        if (!snake2->move()) {
            snake2->applyPenalty(penaltyPerCentForGameQuitOnMultiPlayer);
            culpritSnake = std::make_shared<BodyColor>(snake2->color);
            canKeepGoing = false;
        }
    }

    // refresh food
    try {
        for (int i = 0; i < NUM_FOOD_ITEMS_MULTIPLAYER; i++) {
            (*foodContainer)[i]->genFood();
        }
    } catch (GridSpaceFullError &) {
        canKeepGoing = false;
    }

    // displaying everything on screen
    gameWin->render(background);
    gameWin->render(snake1->font->getItem());
    gameWin->render(snake2->font->getItem());
    for (int i = 0; i < ROWS(); i++) {
        for (int j = 0; j < COLS(); j++) {
            if (arr[i][j] != nullptr) {
                gameWin->render(arr[i][j]);
            }
        }
    }

    if (!canKeepGoing) {
        stopGame(true);
    }

    gameWin->display();
}

void Game::stopGame(const bool isMultiplayer) const {
    if (parent->m_timer.IsRunning()) {
        parent->m_timer.Stop();
    }

    if (isMultiplayer) {
        // waiting for the game over music to finish (only if exists)
        if (Sound::hasSound) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        gameWin->clearRen();
        parent->quit(penaltyPerCentForGameQuitOnMultiPlayer, culpritSnake);
    } else {
        // waiting for the game over music to finish (only if exists)
        if (Sound::hasSound) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        gameWin->clearRen();
        parent->quit();
    }
}

Game::~Game() {
    gameWin->hide();
    gameWin = nullptr;
    SDL_DestroyTexture(background);
    background = nullptr;

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::resume() {
    isPaused = false;
    isKeyPressed = false;
}

void Game::setDir(const Dir currentDir, const Moves &dirs) {
    for (int i = 0; i <= NUM_CHAINED_MOVES_ALLOWED; i++) {
        if ((*dirs)[i] != none) {
            continue;
        }

        (*dirs)[i] = currentDir;
        break;
    }
}

void Game::setDir(const Dir currentDir, const Moves &dirs, const std::shared_ptr<bool> &snake_moved) {
    for (int i = 0; i <= NUM_CHAINED_MOVES_ALLOWED; i++) {
        if ((*dirs)[i] != none) {
            continue;
        }

        (*dirs)[i] = currentDir;
        break;
    }

    *snake_moved = true;
}

Moves Game::resetDirs() {
    // setting chained inputs (directions) to none
    auto dirs = std::make_shared<std::array<Dir, NUM_CHAINED_MOVES_ALLOWED> >();
    for (int i = 0; i < NUM_CHAINED_MOVES_ALLOWED; i++) {
        (*dirs)[i] = none;
    }

    return dirs;
}
