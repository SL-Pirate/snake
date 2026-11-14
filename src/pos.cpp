#include "entity.hpp"

Pos::Pos(const int x, const int y) {
    this->x = x;
    this->y = y;
}

int Pos::getX() const {
    return this->x;
}

int Pos::getY() const {
    return this->y;
}
