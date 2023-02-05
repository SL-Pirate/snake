#include "error.hpp"

const char *SDL_InitError::what(){
    return "Failed to initialize SDL";
    // errMsg = ;
    // return errMsg.c_str();
}

const char *ImageInitError::what(){
    return "Failed to initialize SDL_image";
    // errMsg = "Failed to initialize SDL_image";
    // return errMsg.c_str();
}

const char *TTF_InitError::what(){
    return "Failed to initialize SDL_ttf";
    // errMsg = "Failed to initialize SDL_ttf";
    // return errMsg.c_str();
}