#pragma once
#include "main.hpp"

class Sound{
    Mix_Chunk *sfx = nullptr;
    static int volume;

    public:
    // SDL_AudioSpec audio;
    static bool hasSound;

    Sound(std::string path);
    ~Sound();

    void setVolume(int volume); //insert a volume value from 0 to 100
    int getVolume();            //returns the volume value from 0 to 100 
    void play();
};