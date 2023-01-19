#pragma once

class GraphicItem;

class Window{
    SDL_Window *win = nullptr;

    public:
    Window(const char *title, int h, int w);
    ~Window();

    void setBg();
    void clearRen();
    void render(SDL_Texture *texture);
    void render(GraphicItem *item);
    void display();
    SDL_Texture *loadTexture(const char *filePath);

    SDL_Renderer *ren = nullptr;
};