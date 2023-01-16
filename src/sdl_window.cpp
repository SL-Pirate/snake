#include "main.hpp"

Window::Window(const char *title, int h, int w){
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w ,h, SDL_WINDOW_SHOWN);

    if (win == nullptr){
        std::cout << "Window initialization failed! \nError: " << SDL_GetError() << std::endl;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == nullptr){
        std::cout << "Renderer initialization failed! \nError: " << SDL_GetError() << std::endl;
    }
}

Window::~Window(){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void Window::setBg(){
    //Set colour of renderer
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);

    //Clear the screen to the set colour
    SDL_RenderClear(ren);

    //Show all the has been done behind the scenes
    SDL_RenderPresent(ren);
}