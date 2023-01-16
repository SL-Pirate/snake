#pragma once

class Window{
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;

    public:
    Window(const char *title, int h, int w);
    ~Window();

    void setBg();
};