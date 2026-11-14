#include "entity.hpp"

GraphicItem::GraphicItem(const std::shared_ptr<SDL_Texture> &texture, const int x, const int y, const ID id) {
    this->texture = texture;
    this->id = id;

    org = std::make_unique<SDL_Rect>();
    org->h = 16;
    org->w = 16;
    org->x = 0;
    org->y = 0;

    dst = std::make_shared<SDL_Rect>();
    dst->w = 16;
    dst->h = 16;
    dst->x = x * dst->w;
    dst->y = y * dst->h;

    this->x = x * dst->w;
    this->y = y * dst->h;
}

GraphicItem::GraphicItem(
    const std::shared_ptr<SDL_Texture> &texture,
    const int x,
    const int y,
    const ID id,
    Entity *parent
) {
    this->texture = texture;
    this->id = id;
    this->parent = parent;

    org = std::make_unique<SDL_Rect>();
    org->h = 16;
    org->w = 16;
    org->x = 0;
    org->y = 0;

    dst = std::make_unique<SDL_Rect>();
    dst->w = 16;
    dst->h = 16;
    dst->x = x * dst->w;
    dst->y = y * dst->h;

    this->x = x * dst->w;
    this->y = y * dst->h;
}

GraphicItem::GraphicItem(
    const std::shared_ptr<SDL_Texture> &texture,
    const std::shared_ptr<SDL_Rect> &dst
) : x(0), y(0), id() {
    this->texture = texture;
    this->dst = dst;
}

void GraphicItem::setPos(const int pX, const int pY) {
    this->x = pX * dst->w;
    this->y = pY * dst->h;
}

std::shared_ptr<Pos> GraphicItem::getPos() {
    pos = std::make_shared<Pos>(x / dst->w, y / dst->h);
    return pos;
}

void GraphicItem::rmFromParent() const {
    parent->clearItem();
}
