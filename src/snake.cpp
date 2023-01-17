#include "snake.hpp"

Entity::Entity(){}

Snake::Snake(Window *gameWin, GraphicItem ***arr){
    this->gameWin = gameWin;
    this->arr = arr;
    texture = gameWin->loadTexture("/home/slpirate/Commons/programming/C++/snake/res/gfx/body.png"); // res/gfx/body.png

    snake[0] = new GraphicItem(texture, (int) rows/2, (int) cols/2, SNAKE);
    snake[1] = new GraphicItem(texture, (int) rows/2 + 1, (int) cols/2, SNAKE);
    length = 2;
}

bool Snake::addToArr(){
    //collision detection
    if (arr[snake[0]->getPos()[0]][snake[0]->getPos()[1]] != nullptr){
        if(arr[snake[0]->getPos()[0]][snake[0]->getPos()[1]]->id == WALL || arr[snake[0]->getPos()[0]][snake[0]->getPos()[1]]->id == SNAKE){
            return false;
        }
    }
    else{
        for (int i = 0; i < length; i++){
            arr[snake[i]->getPos()[0]][snake[i]->getPos()[1]] = snake[i];
        }
    }
    return true;
}

bool Snake::move(){
    for (int i = length; i >= 1; i--){
        snake[i] = snake[i - 1];
    }
    switch (dir){
        case up:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0], snake[1]->getPos()[1] - 1, SNAKE);
            break;
        case down:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0], snake[1]->getPos()[1] + 1, SNAKE);
            break;
        case left:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0] - 1, snake[1]->getPos()[1], SNAKE);
            break;
        case right:
            snake[0] = new GraphicItem(texture, snake[1]->getPos()[0] + 1, snake[1]->getPos()[1], SNAKE);
    }

    return addToArr();
}

bool Snake::move(Dir direction){
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

    return move();
}
