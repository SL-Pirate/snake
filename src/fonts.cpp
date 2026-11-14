#include "entity.hpp"
#include "sdl_window.hpp"

Fonts::Fonts(
    Window *gameWin,
    const std::string &title,
    const BodyColor color,
    const int x,
    const int y
) {
    this->gameWin = gameWin;
    this->color = color;

    font = TTF_OpenFontRW(openRes("fonts/LiberationSans-Bold.ttf"), 1, 72);
    if (font == nullptr) {
        std::cout << "could not load fonts " << SDL_GetError() << std::endl;
    }

    dst = new SDL_Rect();
    dst->h = 25;
    dst->w = 100;
    dst->x = x; // 190;
    dst->y = y; // 500;

    setTitle(title);
}

Fonts::~Fonts() {
    delete (dst);
    dst = nullptr;
}

void Fonts::setTitle(const std::string &pTitle) {
    this->title = pTitle;

    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *textSurf = nullptr;
    switch (color) {
        case RED:
            textSurf = TTF_RenderText_Blended(font, pTitle.c_str(), {.r = 225, .g = 0, .b = 0});
            break;
        case BLUE:
            textSurf = TTF_RenderText_Blended(font, pTitle.c_str(), {.r = 0, .g = 0, .b = 225});
            break;
        default:
            textSurf = TTF_RenderText_Blended(font, pTitle.c_str(), {.r = 225, .g = 0, .b = 0});
    }

    texture = SDL_CreateTextureFromSurface(gameWin->ren, textSurf);

    SDL_FreeSurface(textSurf);
    textSurf = nullptr;

    item = std::make_shared<GraphicItem>(texture, dst);
}

void Fonts::clearItem() {
}

std::shared_ptr<GraphicItem> Fonts::getItem() const {
    return item;
}
