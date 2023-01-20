#include "main.hpp"
#include "snake.hpp"
#include "sdl_window.hpp"

Wall::Wall(Window *gameWin, GraphicItem ***arr){
    this->gameWin = gameWin;
    this->arr = arr;
    texture = gameWin->loadTexture(realP "res/gfx/brick_wall23.png"); //res/gfx/brick_wall23.png

    for (int i = 0; i < COLS; i++){
        arr[0][i] = new GraphicItem(texture, 0, i, WALL);
        arr[ROWS - 1][i] = new GraphicItem(texture, ROWS - 1, i, WALL);
    }
    for (int i = 1; i < ROWS - 1; i++){
        for (int j = 0; j < COLS; j++){
            if (j == 0 || j == COLS - 1){
                arr[i][j] = new GraphicItem(texture, i, j, WALL);
            }
        }
    }
}

void Wall::clearItem(){
    item = nullptr;
}
