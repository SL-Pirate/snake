#include "main.hpp"
#include "entity.hpp"
#include "sdl_window.hpp"

Wall::Wall(Window *gameWin, Arena *arena) {
    this->gameWin = gameWin;
    this->arr = arena;
    texture = gameWin->loadTexture(openRes("gfx/brick_wall23.png")); //res/gfx/brick_wall23.png

    for (int i = 0; i < COLS(); i++) {
        (*arr)[0][i] = std::make_shared<GraphicItem>(texture, 0, i, WALL);
        (*arr)[ROWS() - 1][i] = std::make_shared<GraphicItem>(texture, ROWS() - 1, i, WALL);
    }
    for (int i = 1; i < ROWS() - 1; i++) {
        for (int j = 0; j < COLS(); j++) {
            if (j == 0 || j == COLS() - 1) {
                (*arr)[i][j] = std::make_shared<GraphicItem>(texture, i, j, WALL);
            }
        }
    }
}

void Wall::clearItem() {
    item = nullptr;
}
