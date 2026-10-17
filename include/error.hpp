#pragma once

#include <iostream>

class SDL_InitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *
    what() const noexcept override;
};

class ImageInitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const noexcept override;
};

class TTF_InitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const noexcept override;
};

class GridSpaceFullError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const noexcept override;
};
