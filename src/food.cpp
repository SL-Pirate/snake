#include "snake.hpp"

Food::Food(Window *gameWin, GraphicItem ***arr){
    this->arr = arr;
    this->gameWin = gameWin;
    texture = gameWin->loadTexture(realP "res/gfx/egg.png");

    srand(time(0));

    genFood();
}

void Food::genFood(){
    if(item == nullptr){
        genCords();
        if (arr[cords[0]][cords[1]] == nullptr){
            item = new GraphicItem(texture, cords[0], cords[1], FOOD, this);
            arr[cords[0]][cords[1]] = item;
        }
        else{
            genFood();
        }
    }
}

void Food::genCords(){
    cords[0] = random() % cols;
    cords[1] = random() % rows;
}

void Food::clearItem(){
    item = nullptr;
    std::cout << "cleared: " << item << std::endl;
}