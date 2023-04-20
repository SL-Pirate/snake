#include <iostream>

class SDL_InitError : public std::exception{
    std::string errMsg;

    public:
    const char *what();
};

class ImageInitError : public std::exception{
    std::string errMsg;

    public:
    const char *what();
};

class TTF_InitError : public std::exception{
    std::string errMsg;

    public:
    const char *what();
};
