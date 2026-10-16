#include "sound.hpp"

bool Sound::hasSound = false;
int Sound::volume = 128;

Sound::Sound(const std::string &path) {
    if (hasSound) {
        sfx = Mix_LoadWAV_RW(openRes(path), 1);
    }
    if (sfx != nullptr) {
        Mix_VolumeChunk(sfx, getVolume());
    }
}

Sound::~Sound() {
    Mix_FreeChunk(sfx);
    sfx = nullptr;
}

void Sound::play() const {
    Mix_PlayChannel(-1, sfx, 0);
}

void Sound::setVolume(const int pVolume) {
    volume = pVolume / 100 * 128;
}

int Sound::getVolume() {
    return volume / 128 * 100;
}
