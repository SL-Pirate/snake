#include "snake.hpp"

Fonts::Fonts(Window *gameWin, std::string title, BodyColor color, int x, int y){
    this->gameWin  = gameWin;
    this->color = color;

    font = TTF_OpenFont(realP "res/fonts/LiberationSans-Bold.ttf", 72);
    // if (font == nullptr){
    //     std::cout << "could not load fonts " << SDL_GetError() << std::endl;
    // }

    dst = new SDL_Rect();
    dst->h = 25;
    dst->w = 100;
    dst->x = x;   //190;
    dst->y = y;   //500;

    setTitle(title);
}

Fonts::~Fonts(){
    font = nullptr;
    delete(dst);
    dst = nullptr;
}

void Fonts::setTitle(std::string title){
    this->title = title;

    if (texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *textSurf = nullptr;
    switch(color){
        case RED:
            textSurf = TTF_RenderText_Blended(font, title.c_str(), {225, 0, 0});
            break;
        case BLUE:
            textSurf = TTF_RenderText_Blended(font, title.c_str(), {0, 0, 225});
            break;
        default:
            textSurf = TTF_RenderText_Blended(font, title.c_str(), {225, 0, 0});
    }

    texture = SDL_CreateTextureFromSurface(gameWin->ren, textSurf);

    SDL_FreeSurface(textSurf);
    textSurf = nullptr;

    item = new GraphicItem(texture, dst);
}

void Fonts::clearItem(){
    delete (item);
}

GraphicItem *Fonts::getItem(){
    return item;
}