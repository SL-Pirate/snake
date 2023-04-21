#include "error.hpp"

const char *SDL_InitError::what(){
    return "Failed to initialize SDL";
}

const char *ImageInitError::what(){
    return "Failed to initialize SDL_image";
}

const char *TTF_InitError::what(){
    return "Failed to initialize SDL_ttf";
}

const char *GridSpaceFullError::what(){
    return "No space left on grid";
}