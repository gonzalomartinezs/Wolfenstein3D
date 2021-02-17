#include "SoundsContainer.h"

#define BACK_MUSIC "resources/music.wav"

SoundsContainer::SoundsContainer() {
    _loadMusic();
    _loadSFX();
}

Music *SoundsContainer::getMusic(SoundID id) {
    return music.at(id);
}

SoundEffect *SoundsContainer::getSFX(SoundID id) {
    return sfx.at(id);
}

SoundsContainer::~SoundsContainer() {
    for(auto& _music: music){
        delete _music.second;
        _music.second = nullptr;
    }
    for(auto& _sfx: sfx){
        delete _sfx.second;
        _sfx.second = nullptr;
    }
}

void SoundsContainer::_loadMusic() {
    this->music.emplace(BackMusic, new Music(BACK_MUSIC));
}

void SoundsContainer::_loadSFX() {

}
