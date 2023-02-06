#include "sound.hpp"

bool Sound::hasSound = false;
int Sound::volume = 128;

Sound::Sound(std::string path){
    if(hasSound){
        sfx = Mix_LoadWAV(path.c_str());
    }
    if(sfx != nullptr){
        Mix_VolumeChunk(sfx, getVolume());

    }
}

Sound::~Sound(){
    Mix_FreeChunk(sfx);
    sfx = nullptr;
}

void Sound::play(){
    Mix_PlayChannel(-1, sfx, 0);
}

void Sound::setVolume(int volume){
    this->volume = volume / 100 * 128;
}

int Sound::getVolume(){
    return volume / 128 * 100;
}