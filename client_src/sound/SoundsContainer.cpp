#include "SoundsContainer.h"

#define BACK_MUSIC "../client_src/sound/resources/music.wav"
#define KNIFE_SFX "../client_src/sound/resources/knife.wav"
#define PISTOL_SFX "../client_src/sound/resources/real_pistol.wav"
#define MACHINEGUN_SFX "../client_src/sound/resources/machine.wav"
#define CHAINGUN_SFX "../client_src/sound/resources/chain.wav"
#define RPG_SFX "../client_src/sound/resources/rpg.wav"
#define DOG_STEP "../client_src/sound/resources/dog_step.wav"
#define STEP_1 "../client_src/sound/resources/step_1.wav"
#define STEP_2 "../client_src/sound/resources/step_2.wav"
#define HEAVY_STEP "../client_src/sound/resources/heavy_step.wav"
#define DOOR "../client_src/sound/resources/door.wav"
#define PASSAGE "../client_src/sound/resources/passage.wav"
#define LB_TITLE "../client_src/sound/resources/lb_title.wav"
#define LB_NAME "../client_src/sound/resources/lb_name.wav"
#define LB_VALUE "../client_src/sound/resources/lb_value.wav"
#define LB_MUSIC "../client_src/sound/resources/lb_music.wav"

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
    this->music.emplace(LB_Music, LB_MUSIC);
}

void SoundsContainer::_loadSFX() {
    this->sfx.emplace(KnifeSFX, KNIFE_SFX);
    this->sfx.emplace(PistolSFX, PISTOL_SFX);
    this->sfx.emplace(MachineGunSFX, MACHINEGUN_SFX);
    this->sfx.emplace(ChainGunSFX, CHAINGUN_SFX);
    this->sfx.emplace(RPGSFX, RPG_SFX);
    this->sfx.emplace(DogStep, DOG_STEP);
    this->sfx.emplace(Step_1, STEP_1);
    this->sfx.emplace(Step_2, STEP_2);
    this->sfx.emplace(HeavyStep, HEAVY_STEP);
    this->sfx.emplace(DoorMoving, DOOR);
    this->sfx.emplace(PassageMoving, PASSAGE);
    this->sfx.emplace(LB_Title, LB_TITLE);
    this->sfx.emplace(LB_Value, LB_VALUE);
    this->sfx.emplace(LB_Name, LB_NAME);
}
