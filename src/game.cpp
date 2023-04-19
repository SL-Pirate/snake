#include "game.hpp"
#include "sdl_window.hpp"
#include "snake.hpp"
#include "error.hpp"
#include "sound.hpp"

Game::Game(cMain *parent){
    this->parent = parent;
    if (!IMG_Init(IMG_INIT_PNG)){
        gameRunning = false;
        throw ImageInitError();
    }
    if (TTF_Init() == -1){
        gameRunning = false;
        throw TTF_InitError();
    }
    Mix_Init(MIX_INIT_MP3);
    if(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        Sound::hasSound = false;
    }
    else{
        Sound::hasSound = true;
    }
}

void Game::start(){
    gameWin = new Window("Snake", winHeight + 44, winWidth);
    background = gameWin->loadTexture(realP "res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg
    foods = new Food*[numFoodItemsSinglePlayer];

    // arr[ROWS()][COLS()]
    //equates to arr[y][x]
    arr = new GraphicItem**[ROWS()];
    for (int i = 0; i < ROWS(); i++){
        arr[i] = new GraphicItem*[COLS()];
    }

    for (int i = 0; i < ROWS(); i++){
        for (int j = 0; j < COLS(); j++){
            arr[i][j] = nullptr;
        }
    }

    wall = new Wall(gameWin, arr);

    //implementing snake & food
    snake = new Snake(gameWin, arr, parent->difficulty/*1000/parent->difficulty->GetValue()*/, RED);
    for (int i = 0; i < numFoodItemsSinglePlayer; i++){
        foods[i] = new Food(gameWin, arr);
    }

    Dir *dirs = resetDirs();

    while(gameRunning) {
        
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            else if (evnt.type == SDL_KEYDOWN){
                switch(evnt.key.keysym.sym){
                    case SDLK_UP:
                        isKeyPressed = true;
                        setDir(up, dirs);
                        break;
                    case SDLK_DOWN:
                        isKeyPressed = true;
                        setDir(down, dirs);
                        break;
                    case SDLK_LEFT:
                        isKeyPressed = true;
                        setDir(left, dirs);
                        break;
                    case SDLK_RIGHT:
                        isKeyPressed = true;
                        setDir(right, dirs);
                        break;
                    case SDLK_ESCAPE:
                        isKeyPressed = true;
                        isPaused = true;
                        parent->pause();
                        break;
                    case SDLK_q:
                        gameRunning = false;
                }
            }
        }

        gameWin->clearRen();

        //move the snake
        if (isKeyPressed){
            if (!isPaused){
                if(!snake->move(dirs)){
                    gameRunning = false;
                }
                dirs = resetDirs();
                isKeyPressed = false;
            }
        }
        else{
            if(!snake->move()){
                gameRunning = false;
            }
        }
    
        //refresh food
        for (int i = 0; i < numFoodItemsSinglePlayer; i++){
            foods[i]->genFood();
        }

        //displaying everything on screen
        gameWin->render(background);
        gameWin->render((snake->font->getItem()));
        for (int i = 0; i < ROWS(); i++){
            for (int j = 0; j < COLS(); j++){
                if (arr[i][j] != nullptr){
                    gameWin->render(arr[i][j]);
                }
            }
        }

        gameWin->display();
        int sleeptime = 1000 / parent->difficulty->GetValue();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }

    //waiting for the game over music to finish (only if exists)
    if(Sound::hasSound){
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    parent->quit();
    for (int i = 0; i < numFoodItemsSinglePlayer; i++){
        delete (foods[i]);
        foods[i] = nullptr;
    }
    delete(this);
}

void Game::startMultiplayer(){
    gameWin = new Window("Snake", winHeight + 44, winWidth);
    background = gameWin->loadTexture(realP "res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg
    foods = new Food*[numFoodItemsMultiPlayer];

    // arr[ROWS()][COLS()]
    //equates to arr[y][x]
    arr = new GraphicItem**[ROWS()];
    for (int i = 0; i < ROWS(); i++){
        arr[i] = new GraphicItem*[COLS()];
    }

    for (int i = 0; i < ROWS(); i++){
        for (int j = 0; j < COLS(); j++){
            arr[i][j] = nullptr;
        }
    }

    wall = new Wall(gameWin, arr);

    //implementing snake & food
    snake1 = new Snake(gameWin, arr, parent->difficulty/*1000/parent->difficulty->GetValue()*/, RED);
    snake2 = new Snake(gameWin, arr, parent->difficulty/*1000/parent->difficulty->GetValue()*/, BLUE);
    snake->setInitialDir(left);
    for (int i = 0; i < numFoodItemsMultiPlayer; i++){
        foods[i] = new Food(gameWin, arr);
    }

    Dir *dir1 = resetDirs();
    Dir *dir2 = resetDirs();

    bool *snake1_moved = new bool(false);
    bool *snake2_moved = new bool(false);

    while(gameRunning) {
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            else if (evnt.type == SDL_KEYDOWN){
                switch(evnt.key.keysym.sym){
                    case SDLK_UP:
                        isKeyPressed = true;
                        setDir(up, dir1, snake1_moved);
                        break;
                    case SDLK_DOWN:
                        isKeyPressed = true;
                        setDir(down, dir1, snake1_moved);
                        break;
                    case SDLK_LEFT:
                        isKeyPressed = true;
                        setDir(left, dir1, snake1_moved);
                        break;
                    case SDLK_RIGHT:
                        isKeyPressed = true;
                        setDir(right, dir1, snake1_moved);
                        break;
                    case SDLK_w:
                        isKeyPressed = true;
                        setDir(up, dir2, snake2_moved);
                        break;
                    case SDLK_s:
                        isKeyPressed = true;
                        setDir(down, dir2, snake2_moved);
                        break;
                    case SDLK_a:
                        isKeyPressed = true;
                        setDir(left, dir2, snake2_moved);
                        break;
                    case SDLK_d:
                        isKeyPressed = true;
                        setDir(right, dir2, snake2_moved);
                        break;
                    case SDLK_ESCAPE:
                        isKeyPressed = true;
                        isPaused = true;
                        parent->pause();
                        break;
                    case SDLK_q:
                        gameRunning = false;
                }
            }
        }

        gameWin->clearRen();

        //move the snake
        if (isKeyPressed){
            if (!isPaused){
                if(snake1_moved){
                    gameRunning = snake1->move(dir1);
                    *snake1_moved = false;
                    dir1 = resetDirs();
                }

                if(snake2_moved){
                    gameRunning = snake2->move(dir2);
                    *snake2_moved = false;
                    dir2 = resetDirs();
                }
                isKeyPressed = false;
            }
        }
        else{
            if(!snake1->move()){
                snake1->applyPenalty();
                gameRunning = false;
            }
            if(!snake2->move()){
                snake2->applyPenalty();
                gameRunning = false;
            }
        }
    
        //refresh food
        for (int i = 0; i < numFoodItemsMultiPlayer; i++){
            foods[i]->genFood();
        }

        //displaying everything on screen
        gameWin->render(background);
        gameWin->render((snake1->font->getItem()));
        gameWin->render((snake2->font->getItem()));
        for (int i = 0; i < ROWS(); i++){
            for (int j = 0; j < COLS(); j++){
                if (arr[i][j] != nullptr){
                    gameWin->render(arr[i][j]);
                }
            }
        }

        gameWin->display();
        int sleeptime = 1000 / parent->difficulty->GetValue();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
    }

    //waiting for the game over music to finish (only if exists)
    if(Sound::hasSound){
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    parent->quit();
    for (int i = 0; i < numFoodItemsMultiPlayer; i++){
        delete (foods[i]);
        foods[i] = nullptr;
    }
    delete(this);
}

Game::~Game(){
    delete(gameWin);
    gameWin = nullptr;
    SDL_DestroyTexture(background);
    background = nullptr;
    //DO NOT free graphic items from anywhere else since they will be already freed from here
    for (int i = 0; i < ROWS(); i++){
        for (int j = 0; j < COLS(); j++){
            delete(arr[i][j]);
        }
       delete(arr[i]);
    }
    delete (arr);
    arr = nullptr;
    delete(snake);
    snake = nullptr;
    delete(snake1);
    snake1 = nullptr;
    delete(snake2);
    snake2 = nullptr;
    delete(wall);
    wall = nullptr;

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::resume(){
    isPaused = false;
}

void Game::setDir(Dir currentDir, Dir *dirs){
    for (int i = 0; i <= maxNumChainedMovesAllowed; i++){
        if (dirs[i] != none){
            continue;
        }
        else {
            dirs[i] = currentDir;
            break;
        }
    }
}

void Game::setDir(Dir currentDir, Dir *dirs, bool *snake_moved){
    for (int i = 0; i <= maxNumChainedMovesAllowed; i++){
        if (dirs[i] != none){
            continue;
        }
        else {
            dirs[i] = currentDir;
            break;
        }
    }

    *snake_moved = true;
}

Dir *Game::resetDirs(){
    // setting chained inputs (directions) to none
    Dir *dirs = new Dir[maxNumChainedMovesAllowed];
    for (int i = 0; i < maxNumChainedMovesAllowed; i++){
        dirs[i] = none;
    }

    return dirs;
}