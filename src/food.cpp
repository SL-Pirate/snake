#include "snake.hpp"

Food::Food(Window *gameWin, GraphicItem ***arr){
    this->arr = arr;
    this->gameWin = gameWin;
    texture = gameWin->loadTexture(realP "res/gfx/egg.png");

    srand(time(0));

    genFood();
}

void Food::genFood(){
    genCords();
    if (arr[cords[0]][cords[1]] == nullptr){
        refresh();
    }
    else{
        genFood();
    }

}

void Food::genCords(){
    cords[0] = random() % cols;
    cords[1] = random() % rows;
}

void Food::refresh(){
    arr[cords[0]][cords[1]] = new GraphicItem(texture, cords[0], cords[1], FOOD);
}