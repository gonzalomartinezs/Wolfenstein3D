#include "Sound.h"

Sound::Sound(float x, float y, SoundID sound) : Positionable(x, y, None) {
    this->sound = sound;
}

SoundID Sound::getSound() {
    return this->sound;
}

Sound::~Sound() {}
