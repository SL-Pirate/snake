#include "main.hpp"
#include "sdl_window.hpp"
#include "snake.hpp"

int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
    }
    if (!IMG_Init(IMG_INIT_PNG)){
        std::cout << "SDL_IMG INIT FAILED! Error: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() == -1){
        std::cout << "TTF INIT FAILED! Error: " << TTF_GetError() << std::endl;
    }

    Window *gameWin = new Window("Snake", winHeight + 44, winWidth);

    SDL_Texture *background = gameWin->loadTexture(realP "res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg

    // arr[rows][cols]
    //equates to arr[y][x]
    GraphicItem ***arr = new GraphicItem**[rows];
    for (int i = 0; i < rows; i++){
        arr[i] = new GraphicItem*[cols];
    }

    bool gameRunning = true;
    bool isKeyPressed = false;
    bool isPaused = false;
    const int numFoodItems = 3;

    SDL_Event evnt;
    Dir dir;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            arr[i][j] = nullptr;
        }
    }

    Wall wall = Wall(gameWin, arr);

    //implementing snake & food
    Snake snake = Snake(gameWin, arr);
    Food *foods[numFoodItems];
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
                if(!snake.move(dir)){
                    gameRunning = false;
                }
                isKeyPressed = false;
            }
        }
        else{
            if(!snake.move()){
                gameRunning = false;
            }
        }
    
        //refresh food
        for (int i = 0; i < numFoodItems; i++){
            foods[i]->genFood();
        }

        //displaying everything on screen
        gameWin->render(background);
        gameWin->render((snake.font->getItem()));
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (arr[i][j] != nullptr){
                    gameWin->render(arr[i][j]);
                }
            }
        }

        gameWin->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    //game over
    system("clear");
    std::cout << "Game Over\nYour Score: " << snake.getScore() << std::endl;

    //freeying memory
    delete(gameWin);
    gameWin = nullptr;
    SDL_DestroyTexture(background);
    background = nullptr;
    //DO NOT free graphic items from anywhere else since they will be already freed from here
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
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

    TTF_Quit;
    SDL_Quit;

    return 0;
}
