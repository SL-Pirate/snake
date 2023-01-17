#include "graphic_handler.hpp"
#include "main.hpp"

GraphicItem::GraphicItem(SDL_Texture *texture, int x, int y){
    this->texture = texture;

    org = new SDL_Rect();
    org->h = 16;
    org->w = 16;
    org->x = 0;
    org->y = 0;

    dst.w = 16;
    dst.h = 16;
    dst.x = x * dst.w;
    dst.y = y * dst.h;

    setPos(x, y);
}

SDL_Rect *GraphicItem::getDst() {
    return &dst;
}

void GraphicItem::setPos(int x, int y){
    this->x = x * dst.w;
    this->y = y * dst.h;
}

int *GraphicItem::getPos(){
    pos = new int[2];
    pos[0] = x / dst.w;
    pos[1] = y / dst.h;
    return pos;
}