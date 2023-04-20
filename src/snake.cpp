#include "snake.hpp"


//Definition of class "Entity" 
//which is the parent class for all entities snke, wall and food
Entity::Entity(){}

Entity::~Entity(){
    SDL_DestroyTexture(texture);
    texture = nullptr;
}


//definition of the actual "Snake" class
Snake::Snake(Window *gameWin, GraphicItem ***arr, wxSlider *difficulty, BodyColor color){
    this->gameWin = gameWin;
    this->arr = arr;
    this->color = color;
    snake = new GraphicItem*[ROWS() * COLS()];
    eatSound = new Sound("res/sfx/boom.wav");
    dieSound = new Sound("res/sfx/aaaugh.wav");
    registeredDirs = new Dir[maxNumChainedMovesAllowed];
    setInitialDir(right);
    
    const char *filePath;

    if (color == RED){
        filePath = "res/gfx/red.png";
        texture = gameWin->loadTexture(filePath); // res/gfx/body.png
        snake[0] = new GraphicItem(texture, (int) ROWS()/2, (int) COLS()/2, SNAKE);
        snake[1] = new GraphicItem(texture, (int) ROWS()/2 + 1, (int) COLS()/2, SNAKE);

        //display scores
        scoreTitle = "Arrows: ";
        font = new Fonts(gameWin, scoreTitle + std::to_string(score), color, winWidth/4-50, winHeight);
    }
    else if(color == BLUE){
        dir = left;
        filePath = "res/gfx/blue.png";
        texture = gameWin->loadTexture(filePath); // res/gfx/body.png
        snake[0] = new GraphicItem(texture, (int) ROWS()/2, (int) COLS()/2 + 1, SNAKE);
        snake[1] = new GraphicItem(texture, (int) ROWS()/2 + 1, (int) COLS()/2 + 1, SNAKE);

        //display scores
        scoreTitle = "WASD: ";
        font = new Fonts(gameWin, scoreTitle + std::to_string(score), color, winWidth*3/4-50, winHeight); 
    }
    
    this->difficulty = difficulty;
    length = 2;
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
    Dir direction = getNextDir();
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
        //Hit the wall (or a snake in that case)
        if(nextItem->id == WALL || nextItem->id == SNAKE){
            dieSound->play();
            return false;
        }
        //ate food
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

bool Snake::move(Dir *dirs){
    delete(registeredDirs);
    registeredDirs = dirs;
    return move();
}

Dir Snake::getNextDir(){
    Dir currentDir = registeredDirs[0];

    //removing second dir from the list
    for (int i = 1; i < maxNumChainedMovesAllowed; i++){
        if (registeredDirs[i] != none){
            registeredDirs[i - 1] = registeredDirs[i];
        }
    }
    registeredDirs[maxNumChainedMovesAllowed] = none;

    return currentDir;
}

void Snake::ate(GraphicItem *nextItem){
    length++;
    score += 10 * difficulty->GetValue();

    //delete the food item
    arr[nextItem->getPos()[0]][nextItem->getPos()[1]]->rmFromParent();
    delete(arr[nextItem->getPos()[0]][nextItem->getPos()[1]]);

    //output the score
    font->setTitle(scoreTitle + std::to_string(score));

    //play sound effect
    eatSound->play();
}

void Snake::setInitialDir(Dir dir){
    registeredDirs[0] = dir;
    for (int i = 1; i < maxNumChainedMovesAllowed; i++){
        registeredDirs[i] = none;
    }
}

void Snake::clearItem(){
    item = nullptr;
}

int Snake::getScore(){
    return score;
}

// apply a penalty for defined amount to the score as a percentage
void Snake::applyPenalty(double penaltyPerCent){
    score -= (int) (score * penaltyPerCent / 100.0);
}
