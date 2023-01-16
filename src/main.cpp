#include "main.hpp"

int main(int argc, char **argv){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error: SDL INIT VIDEO FAILED!" << SDL_GetError() << std::endl;
    }
    if (!IMG_Init(IMG_INIT_PNG)){
        std::cout << "SDL_IMG INIT FAILED! Error: " << SDL_GetError() << std::endl;
    }

    Window *gameWin = new Window("Snake", 600, 600);

    bool gameRunning = true;

    SDL_Event evnt;

    while(gameRunning) {
        while (SDL_PollEvent(&evnt)){
            if (evnt.type == SDL_QUIT){
                gameRunning = false;
            }
            else{
                gameWin->setBg();
            }
        }
    }

    delete(gameWin);
    gameWin = nullptr;
    SDL_Quit;

    return 0;
}