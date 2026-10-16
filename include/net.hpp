#pragma once

#include <vector>
#include <array>

inline bool isNetworkingEnabled = false;

class Payload {
    std::vector<std::array<int, 2> > snake;
    unsigned int score = 0;
    std::array<int, 2> *ateFruit = nullptr;

public:
    Payload(const std::vector<std::array<int, 2> > &snake, unsigned int score, std::array<int, 2> *ate_fruit);

    ~Payload();

    [[nodiscard]] std::vector<std::array<int, 2> > getSnake() const;

    [[nodiscard]] unsigned int getScore() const;

    [[nodiscard]] std::array<int, 2> *getAteFruit() const;
};
