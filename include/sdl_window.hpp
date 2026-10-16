#pragma once

class GraphicItem;

class Window {
    SDL_Window *win = nullptr;

public:
    Window(const char *title, int h, int w);

    ~Window();

    void hide() const;

    void show() const;

    void resize(int h, int w) const;

    void clearRen() const;

    void render(SDL_Texture *texture) const;

    void render(const GraphicItem *item) const;

    void display() const;

    SDL_Texture *loadTexture(SDL_RWops *res) const;

    SDL_Renderer *ren = nullptr;
};
