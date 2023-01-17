#include "main.hpp"
#include "snake.hpp"
#include "sdl_window.hpp"

Wall::Wall(Window *gameWin, GraphicItem ***arr){
    this->gameWin = gameWin;
    this->arr = arr;
    texture = gameWin->loadTexture("/home/slpirate/Commons/programming/C++/snake/res/gfx/brick_wall23.png"); //res/gfx/brick_wall.png

    for (int i = 0; i < cols; i++){
        arr[0][i] = new GraphicItem(texture, 0, i, WALL);
        arr[rows - 1][i] = new GraphicItem(texture, rows - 1, i, WALL);
    }
    for (int i = 1; i < rows - 1; i++){
        for (int j = 0; j < cols; j++){
            if (j == 0 || j == cols - 1){
                arr[i][j] = new GraphicItem(texture, i, j, WALL);
            }
        }
    }
}
