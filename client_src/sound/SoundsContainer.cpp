#include "SoundsContainer.h"

#define BACK_MUSIC "../client_src/sound/resources/music.wav"
#define KNIFE_SFX "../client_src/sound/resources/knife.wav"
#define PISTOL_SFX "../client_src/sound/resources/pistol.wav"

SoundsContainer::SoundsContainer() {
    _loadMusic();
    _loadSFX();
}

Music& SoundsContainer::getMusic(SoundID id) {
    return music.at(id);
}

SoundEffect& SoundsContainer::getSFX(SoundID id) {
    return sfx.at(id);
}

SoundsContainer::~SoundsContainer() {}

void SoundsContainer::_loadMusic() {
    this->music.emplace(BackMusic, BACK_MUSIC);
}

void SoundsContainer::_loadSFX() {
    this->sfx.emplace(KnifeSFX, KNIFE_SFX);
    this->sfx.emplace(PistolSFX, PISTOL_SFX);
    this->sfx.emplace(MachineGunSFX, PISTOL_SFX);
    this->sfx.emplace(ChainGunSFX, PISTOL_SFX);
    this->sfx.emplace(RPGSFX, PISTOL_SFX);
}
