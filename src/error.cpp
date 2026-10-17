#include "error.hpp"

const char *SDL_InitError::what() const noexcept {
    return "Failed to initialize SDL";
}

const char *ImageInitError::what() const noexcept {
    return "Failed to initialize SDL_image";
}

const char *TTF_InitError::what() const noexcept {
    return "Failed to initialize SDL_ttf";
}

const char *GridSpaceFullError::what() const noexcept {
    return "No space left on grid";
}
