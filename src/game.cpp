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
    Dir dir = right;
    for (int i = 0; i < numFoodItems; i++){
        foods[i] = new Food(gameWin, arr);
    }

    while(gameRunning) {
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            else if (evnt.type == SDL_KEYDOWN){
                switch(evnt.key.keysym.sym){
                    case SDLK_UP:
                        isKeyPressed = true;
                        dir = up;
                        break;
                    case SDLK_DOWN:
                        isKeyPressed = true;
                        dir = down;
                        break;
                    case SDLK_LEFT:
                        isKeyPressed = true;
                        dir = left;
                        break;
                    case SDLK_RIGHT:
                        isKeyPressed = true;
                        dir = right;
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
                if(!snake->move(dir)){
                    gameRunning = false;
                }
                isKeyPressed = false;
            }
        }
        else{
            if(!snake->move()){
                gameRunning = false;
            }
        }
    
        //refresh food
        for (int i = 0; i < numFoodItems; i++){
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
    delete(this);
}
void Game::startMultiplayer(){
    gameWin = new Window("Snake", winHeight + 44, winWidth);

    background = gameWin->loadTexture(realP "res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg

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
    Dir dir1 = right;
    snake2 = new Snake(gameWin, arr, parent->difficulty/*1000/parent->difficulty->GetValue()*/, BLUE);
    Dir dir2 = left;
    for (int i = 0; i < numFoodItems; i++){
        foods[i] = new Food(gameWin, arr);
    }

    while(gameRunning) {
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            else if (evnt.type == SDL_KEYDOWN){
                switch(evnt.key.keysym.sym){
                    case SDLK_UP:
                        isKeyPressed = true;
                        dir1 = up;
                        break;
                    case SDLK_DOWN:
                        isKeyPressed = true;
                        dir1 = down;
                        break;
                    case SDLK_LEFT:
                        isKeyPressed = true;
                        dir1 = left;
                        break;
                    case SDLK_RIGHT:
                        isKeyPressed = true;
                        dir1 = right;
                        break;
                    case SDLK_w:
                        isKeyPressed = true;
                        dir2 = up;
                        break;
                    case SDLK_s:
                        isKeyPressed = true;
                        dir2 = down;
                        break;
                    case SDLK_a:
                        isKeyPressed = true;
                        dir2 = left;
                        break;
                    case SDLK_d:
                        isKeyPressed = true;
                        dir2 = right;
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
                if(!snake1->move(dir1)){
                    gameRunning = false;
                }
                if(!snake2->move(dir2)){
                    gameRunning = false;
                }
                isKeyPressed = false;
            }
        }
        else{
            if(!snake1->move()){
                gameRunning = false;
            }
            if(!snake2->move()){
                gameRunning = false;
            }
        }
    
        //refresh food
        for (int i = 0; i < numFoodItems; i++){
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
    for (int i = 0; i < numFoodItems; i++){
        delete (foods[i]);
        foods[i] = nullptr;
    }
    delete(snake);
    delete(snake1);
    delete(snake2);
    delete(wall);

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::resume(){
    isPaused = false;
}