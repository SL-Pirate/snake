#include "net.hpp"

Payload::Payload(const std::vector<std::array<int, 2> > &snake, const unsigned int score, std::array<int, 2> *ate_fruit)
    : snake(snake),
      score(score),
      ateFruit(ate_fruit) {
}

Payload::~Payload() {
    delete ateFruit;
}

[[nodiscard]] std::vector<std::array<int, 2> > Payload::getSnake() const {
    return snake;
}

[[nodiscard]] unsigned int Payload::getScore() const {
    return score;
}

[[nodiscard]] std::array<int, 2> *Payload::getAteFruit() const {
    return ateFruit;
}
