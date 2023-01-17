#include "snake.hpp"

Entity::Entity(){}

Snake::Snake(Window *gameWin, GraphicItem ***arr){
    this->gameWin = gameWin;
    this->arr = arr;
    texture = gameWin->loadTexture("res/gfx/body.png"); // res/gfx/body.png

    snake[0] = new GraphicItem(texture, (int) rows/2, (int) cols/2);
    snake[1] = new GraphicItem(texture, (int) rows/2 + 1, (int) cols/2);
    length = 2;

    addToArr();
}

void Snake::addToArr(){
    for (int i = 0; i < length; i++){
        arr[snake[i]->getPos()[0]][snake[i]->getPos()[1]] = snake[i];
    }
}

void Snake::move(){
    for (int i = length; i >= 1; i--){
        snake[i] = snake[i - 1];
    }
    switch (dir){
        case up:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0], snake[1]->getPos()[1] - 1);
            break;
        case down:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0], snake[1]->getPos()[1] + 1);
            break;
        case left:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0] - 1, snake[1]->getPos()[1]);
            break;
        case right:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0] + 1, snake[1]->getPos()[1]);
    }

    addToArr();
}

void Snake::move(Dir direction){
    if (dir == left && direction != right){
        dir = direction;
    }
    else if (dir == right && direction != left){
        dir = direction;
    }
    else if (dir == up && direction != down){
        dir = direction;
    }
    else if (dir == down && direction != up){
        dir = direction;
    }

    move();
}
