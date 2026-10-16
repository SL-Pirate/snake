#pragma once

#include <iostream>

class SDL_InitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *
    what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class ImageInitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class TTF_InitError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};

class GridSpaceFullError : public std::exception {
    std::string errMsg;

public:
    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};
