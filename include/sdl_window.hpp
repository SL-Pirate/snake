#pragma once

class GraphicItem;

class Window
{
    SDL_Window *win = nullptr;

public:
    Window(const char *title, int h, int w);
    ~Window();

    void hide();
    void show();
    void resize(int h, int w);
    void setBg();
    void clearRen();
    void render(SDL_Texture *texture);
    void render(GraphicItem *item);
    void display();
    SDL_Texture *loadTexture(SDL_RWops *res);

    SDL_Renderer *ren = nullptr;
};