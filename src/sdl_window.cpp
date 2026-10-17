#include <SDL_image.h>
#include <iostream>

#include "sdl_window.hpp"
#include "entity.hpp"

Window::Window(const char *title, int h, int w) {
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
                           SDL_WINDOW_HIDDEN | SDL_WINDOW_ALWAYS_ON_TOP);

    if (win == nullptr) {
        throw std::runtime_error(std::string("Window initialization failed! \nError: ").append(SDL_GetError()).c_str());
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == nullptr) {
        throw std::runtime_error(
            std::string("Renderer initialization failed! \nError: ").append(SDL_GetError()).c_str());
    }
}

Window::~Window() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void Window::hide() const {
    SDL_HideWindow(win);
}

void Window::show() const {
    SDL_ShowWindow(win);
}

void Window::resize(int h, int w) const {
    SDL_SetWindowSize(win, w, h);
}

void Window::clearRen() const {
    SDL_RenderClear(ren);
}

void Window::display() const {
    SDL_RenderPresent(ren);
}

void Window::render(SDL_Texture *texture) const {
    SDL_RenderCopy(ren, texture, nullptr, nullptr);
}

void Window::render(const GraphicItem *item) const {
    SDL_RenderCopy(ren, item->texture, item->org, item->dst);
}

SDL_Texture *Window::loadTexture(SDL_RWops *res) const {
    SDL_Texture *texture = IMG_LoadTexture_RW(ren, res, 1);

    if (texture == nullptr) {
        // std::cout << "Loading texture file " << filePath << " failed with Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}
