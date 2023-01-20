#include "game.hpp"
#include "sdl_window.hpp"
#include "snake.hpp"

Game::Game(cMain *parent){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        // std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
    }
    if (!IMG_Init(IMG_INIT_PNG)){
        // std::cout << "SDL_IMG INIT FAILED! Error: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() == -1){
        // std::cout << "TTF INIT FAILED! Error: " << TTF_GetError() << std::endl;
    }

    gameWin = new Window("Snake", winHeight + 44, winWidth);

    background = gameWin->loadTexture(realP "res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg

    // arr[ROWS][COLS]
    //equates to arr[y][x]
    arr = new GraphicItem**[ROWS];
    for (int i = 0; i < ROWS; i++){
        arr[i] = new GraphicItem*[COLS];
    }

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            arr[i][j] = nullptr;
        }
    }

    wall = new Wall(gameWin, arr);

    //implementing snake & food
    snake = new Snake(gameWin, arr, 1000/parent->difficulty->GetValue());
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
                        isPaused = (isPaused) ? false : true;
                        parent->pause();
                        break;
                    case SDLK_q:
                        gameRunning = false;
                        parent->quit();
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
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                if (arr[i][j] != nullptr){
                    gameWin->render(arr[i][j]);
                }
            }
        }

        gameWin->display();
        int sleeptime = 1000 / parent->difficulty->GetValue();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
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
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
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
    delete(wall);

    TTF_Quit;
    SDL_Quit;
}

void Game::resume(){
    isPaused = false;
}