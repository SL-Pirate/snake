#include "main.hpp"
#include "sdl_window.hpp"
#include "snake.hpp"

Window::Window(const char *title, int h, int w){
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w ,h, SDL_WINDOW_SHOWN);

    if (win == nullptr){
        // std::cout << "Window initialization failed! \nError: " << SDL_GetError() << std::endl;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == nullptr){
        // std::cout << "Renderer initialization failed! \nError: " << SDL_GetError() << std::endl;
    }
}

Window::~Window(){
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void Window::clearRen(){
    SDL_RenderClear(ren);
}

void Window::display(){
    SDL_RenderPresent(ren);
}

void Window::render(SDL_Texture *texture){
    SDL_RenderCopy(ren, texture, NULL, NULL);
}

void Window::render(GraphicItem *item){
    SDL_RenderCopy(ren, item->texture, item->org, item->dst);
}

SDL_Texture *Window::loadTexture(const char *filePath){
    SDL_Texture *texture = IMG_LoadTexture(ren, filePath);

    if (texture == nullptr){
        // std::cout << "Loading texture file " << filePath << " failed with Error: " << SDL_GetError() << std::endl;
    }
    
    return texture;
}