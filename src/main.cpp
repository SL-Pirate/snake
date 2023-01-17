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

    Window *gameWin = new Window("Snake", winWidth, winHeight);

    SDL_Texture *background = gameWin->loadTexture("/home/slpirate/Commons/programming/C++/snake/res/gfx/grass-pattern.jpg"); // res/gfx/grass-pattern.jpg

    // arr[rows][cols]
    //equates to arr[y][x]
    GraphicItem ***arr = new GraphicItem**[rows];
    for (int i = 0; i < rows; i++){
        arr[i] = new GraphicItem*[cols];
    }

    //implementing snake
    Snake snake = Snake(gameWin, arr);

    bool gameRunning = true;
    bool isKeyPressed = false;

    SDL_Event evnt;
    Dir dir;

    while(gameRunning) {
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            if (evnt.type == SDL_KEYDOWN){
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
                }
            }
        }
        gameWin->clearRen();

        //cleaning the arr
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                arr[i][j] = nullptr;
            }
        }

        //poppulating the array w/ walls
        Wall wall = Wall(gameWin, arr);

        //move the snake
        if (isKeyPressed){
            snake.move(dir);
            isKeyPressed = false;
        }
        else{
            snake.move();
        }

        //displaying everything on screen
        gameWin->render(background);

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++){
                if (arr[i][j] != nullptr){
                    gameWin->render(arr[i][j]);
                }
            }
        }
        gameWin->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    delete(gameWin);
    gameWin = nullptr;
    SDL_Quit;

    return 0;
}