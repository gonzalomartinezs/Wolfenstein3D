#include "SoundEffect.h"
#include "../Exceptions/SDLException.h"

SoundEffect::SoundEffect(std::string path) {
    this->sfx = Mix_LoadWAV(path.c_str());
    if (this->sfx == nullptr)
        throw SDLException("Unable to load sound effect file");
}

void SoundEffect::play(int loops) {
    Mix_PlayChannel(-1, this->sfx, loops);
}

void SoundEffect::setVolume(float relative_volume) {
    Mix_Volume(-1, int(relative_volume * MIX_MAX_VOLUME));
}

SoundEffect::~SoundEffect() {
    if(this->sfx){
        Mix_FreeChunk(this->sfx);
        this->sfx = nullptr;
    }
}
