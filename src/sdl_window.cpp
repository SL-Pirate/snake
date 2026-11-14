#include <SDL_image.h>

#include "sdl_window.hpp"
#include "entity.hpp"

Window::Window(const char *title, const int h, const int w) {
    win = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w,
        h,
        SDL_WINDOW_HIDDEN | SDL_WINDOW_ALWAYS_ON_TOP
    );

    if (win == nullptr) {
        // std::cout << "Window initialization failed! \nError: " << SDL_GetError() << std::endl;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if (ren == nullptr) {
        // std::cout << "Renderer initialization failed! \nError: " << SDL_GetError() << std::endl;
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

void Window::render(const std::shared_ptr<SDL_Texture> &texture) const {
    SDL_RenderCopy(ren, texture.get(), nullptr, nullptr);
}

void Window::render(const std::shared_ptr<GraphicItem> &item) const {
    SDL_RenderCopy(ren, item->texture.get(), item->org.get(), item->dst.get());
}

std::shared_ptr<SDL_Texture> Window::loadTexture(SDL_RWops *res) const {
    const std::shared_ptr<SDL_Texture> texture(IMG_LoadTexture_RW(ren, res, 1), SDL_DestroyTexture);

    if (texture == nullptr) {
        // std::cout << "Loading texture file " << filePath << " failed with Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}
