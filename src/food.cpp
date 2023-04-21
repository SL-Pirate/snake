#include "entity.hpp"

Food::Food(Window *gameWin, GraphicItem ***arr){
    this->arr = arr;
    this->gameWin = gameWin;
    texture = gameWin->loadTexture("res/gfx/egg.png");

    srand(time(0));

    genFood();
}

void Food::genFood(){
    if (item == nullptr){
        int len_emptyCords = 0;

        for (int i = 0; i < ROWS(); i++){
            for (int j = 0; j < COLS(); j++){
                if (arr[i][j] == nullptr){
                    len_emptyCords++;
                }
            }
        }

        int emptyCords[len_emptyCords][2];
        int index_emptyCords = 0;

        for (int i = 0; i < ROWS(); i++){
            for (int j = 0; j < COLS(); j++){
                if (arr[i][j] == nullptr){
                    emptyCords[index_emptyCords][0] = i;
                    emptyCords[index_emptyCords][1] = j;
                    index_emptyCords++;

                    if (index_emptyCords == len_emptyCords){
                        break;
                    }
                }
            }
        }

        int lucky_index = rand() % len_emptyCords;

        int cords[2] = {emptyCords[lucky_index][0], emptyCords[lucky_index][1]};

        item = new GraphicItem(texture, cords[0], cords[1], FOOD, this);
        arr[cords[0]][cords[1]] = item;
    }
}

void Food::clearItem(){
    item = nullptr;
}