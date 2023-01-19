#include "snake.hpp"

GraphicItem::GraphicItem(SDL_Texture *texture, int x, int y, ID id){
    this->texture = texture;
    this->id = id;

    org = new SDL_Rect();
    org->h = 16;
    org->w = 16;
    org->x = 0;
    org->y = 0;

    dst = new SDL_Rect();
    dst->w = 16;
    dst->h = 16;
    dst->x = x * dst->w;
    dst->y = y * dst->h;

    setPos(x, y);
}

GraphicItem::GraphicItem(SDL_Texture *texture, int x, int y, ID id, Entity *parent){
    this->texture = texture;
    this->id = id;
    this->parent = parent;

    org = new SDL_Rect();
    org->h = 16;
    org->w = 16;
    org->x = 0;
    org->y = 0;

    dst = new SDL_Rect();
    dst->w = 16;
    dst->h = 16;
    dst->x = x * dst->w;
    dst->y = y * dst->h;

    setPos(x, y);
}

GraphicItem::GraphicItem(SDL_Texture *texture, SDL_Rect *dst){
    this->texture = texture;

    this->dst = dst;
}

GraphicItem::~GraphicItem(){
    delete (pos);
    delete (org);
    delete (dst);
}

void GraphicItem::setPos(int x, int y){
    this->x = x * dst->w;
    this->y = y * dst->h;
}

int *GraphicItem::getPos(){
    pos = new int[2];
    pos[0] = x / dst->w;
    pos[1] = y / dst->h;
    return pos;
}

void GraphicItem::rmFromParent(){
    parent->clearItem();
}