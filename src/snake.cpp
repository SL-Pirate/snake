#include "snake.hpp"


//Definition of class "Entity" 
//which is the parent class for all entities snke, wall and food
Entity::Entity(){}

Entity::~Entity(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}


//definition of the actual "Snake" class
Snake::Snake(Window *gameWin, GraphicItem ***arr, int scoreMultiplier){
    this->gameWin = gameWin;
    this->arr = arr;
    texture = gameWin->loadTexture(realP "res/gfx/body.png"); // res/gfx/body.png
    this->scoreMultiplier = scoreMultiplier;

    snake[0] = new GraphicItem(texture, (int) ROWS/2, (int) COLS/2, SNAKE);
    snake[1] = new GraphicItem(texture, (int) ROWS/2 + 1, (int) COLS/2, SNAKE);
    length = 2;

    //display scores
    font = new Fonts(gameWin, "SCORE: " + std::to_string(score));
}

void Snake::addToArr(){
    for (int i = 0; i < length; i++){
        arr[snake[i]->getPos()[0]][snake[i]->getPos()[1]] = snake[i];
    }
}

Snake::~Snake(){
    delete(font);
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
    score += scoreMultiplier;

    //delete the food item
    arr[nextItem->getPos()[0]][nextItem->getPos()[1]]->rmFromParent();
    delete(arr[nextItem->getPos()[0]][nextItem->getPos()[1]]);

    //output the score
    font->setTitle("SCORE: " + std::to_string(score));
}

void Snake::clearItem(){
    item = nullptr;
}

int Snake::getScore(){
    return score;
}