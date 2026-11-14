#pragma once

//marcos
#define SDL_MAIN_HANDLED
#define VERSION "v5.2.1"
#define TEXT_WIDTH 16
#define TEXT_HEIGHT 16
#define NUM_FOOD_ITEMS_SINGLE_PLAYER 2
#define NUM_FOOD_ITEMS_MULTIPLAYER 3
#define NUM_CHAINED_MOVES_ALLOWED 3

//for debugging purposes
#include <cmrc/cmrc.hpp>
#include <SDL.h>

CMRC_DECLARE(res);

#define GAME_SCREEN_SCORE_HEIGHT_OFFSET 44

//ENUMs
enum ID { WALL, SNAKE, FOOD };

//enums required to determine the direction of the movement of the snake
enum Dir { up, down, left, right, none };

enum BodyColor { RED, BLUE };

//global vars
inline int winWidth = 496;
inline int winHeight = 496;
//resolves to y
inline int ROWS() {
    return winHeight / 16;
}

//resolves to x
inline int COLS() {
    return winWidth / 16;
}

inline SDL_RWops *openRes(const std::string &name) {
    const auto fs = cmrc::res::get_filesystem();
    const auto file = fs.open(name); // throws if the file doesn't exist
    return SDL_RWFromConstMem(file.begin(), static_cast<int>(file.size()));
}
