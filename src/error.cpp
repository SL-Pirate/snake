#include "error.hpp"

const char *SDL_InitError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Failed to initialize SDL";
}

const char *ImageInitError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Failed to initialize SDL_image";
}

const char *TTF_InitError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "Failed to initialize SDL_ttf";
}

const char *GridSpaceFullError::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
    return "No space left on grid";
}
