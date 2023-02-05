#include "sound.hpp"

bool Sound::hasSound = false;
int Sound::volume = 128;

// Sound::Sound(std::string path){
//     audioFreq = 48000;
//     format = AUDIO_S16;
//     audioChannels = 2;
//     audioSamples = 4096;
// }

// void Sound::setupAudioDevice(){
//     SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
//     want.freq = audioFreq;
//     want.format = format;
//     want.channels = audioChannels;
//     want.samples = audioSamples;
//     want.callback = MyAudioCallback();  // you wrote this function elsewhere.
//     dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
// }

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