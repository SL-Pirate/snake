#pragma once

#include "main.hpp"

#include <SDL_mixer.h>

class Sound {
    Mix_Chunk *sfx = nullptr;
    static int volume;

public:
    // SDL_AudioSpec audio;
    static bool hasSound;

    Sound(const std::string &path);

    ~Sound();

    static void setVolume(int pVolume); //insert a volume value from 0 to 100
    static int getVolume(); //returns the volume value from 0 to 100
    void play() const;
};
