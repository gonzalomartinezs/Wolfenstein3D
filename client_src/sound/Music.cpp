#include "Music.h"
#include "../Exceptions/SDLException.h"

Music::Music(std::string path) {
    this->music = Mix_LoadMUS(path.c_str());
    if (this->music == nullptr)
        throw SDLException("Unable to load music file");
}

void Music::play(int loops) {
    if(!Mix_PlayingMusic())
        Mix_PlayMusic(this->music, loops);
}

void Music::pause() {
    if(Mix_PlayingMusic())
        Mix_PauseMusic();
}

void Music::resume() {
    if(Mix_PlayingMusic() && Mix_PausedMusic())
        Mix_ResumeMusic();
}

void Music::setVolume(float relative_volume) {
    Mix_VolumeMusic(int(relative_volume*MIX_MAX_VOLUME));
}

void Music::stop() {
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
}

Music::~Music() {
    if(this->music){
        stop();
        Mix_FreeMusic(this->music);
        this->music = nullptr;
    }
}


