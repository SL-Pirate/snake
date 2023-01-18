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

void Snake::addToArr(){
    for (int i = 0; i < length; i++){
        arr[snake[i]->getPos()[0]][snake[i]->getPos()[1]] = snake[i];
    }
}

bool Snake::move(){
    //deleting the last square where the snake's tail was last in
    arr[snake[length - 1]->getPos()[0]][snake[length - 1]->getPos()[1]] = nullptr;

    //collision detection
    GraphicItem *nextItem = nullptr;
    switch (dir){
        case up:
            nextItem = arr[snake[0]->getPos()[0]][snake[0]->getPos()[1] - 1];
            break;
        case down:
            nextItem = arr[snake[0]->getPos()[0]][snake[0]->getPos()[1] + 1];
            break;
        case left:
            nextItem = arr[snake[0]->getPos()[0] - 1][snake[0]->getPos()[1]];
            break;
        case right:
            nextItem = arr[snake[0]->getPos()[0] + 1][snake[0]->getPos()[1]];
    }
    if (nextItem != nullptr){
        if(nextItem->id == WALL || nextItem->id == SNAKE){
            return false;
        }
        else if(nextItem->id == FOOD){
            ate(nextItem);
        }
    }
    else{
        delete(snake[length - 1]);
        snake[length - 1] = nullptr;
    }

    for (int i = length - 1; i >= 1; i--){
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

    addToArr();

    return true;
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

void Snake::ate(GraphicItem *nextItem){
    length++;
    score++;

    //delete the food item
    arr[nextItem->getPos()[0]][nextItem->getPos()[1]]->parent->clearItem();
    delete(arr[nextItem->getPos()[0]][nextItem->getPos()[1]]);

    //output the score
    system("clear");
    std::cout << "Your score: " << score << std::endl;
}

void Snake::clearItem(){
    item = nullptr;
}