#include "SoundHandler.h"
#include "sound/SoundID.h"

#define FOREVER -1

enum PlayerInfo {Lives, HP, Weapon, Key, Firing, Ammo, Score};

SoundHandler::SoundHandler(SoundsContainer &sounds): sounds(sounds), last_ammo(0){}

void SoundHandler::startBackMusic() {
    Music& music = this->sounds.getMusic(BackMusic);
    music.play(FOREVER);
    music.setVolume(0.2);
}

SoundHandler::~SoundHandler() {}

void SoundHandler::loadGameSfx(std::vector<int> &player_info) {
    if (last_ammo > player_info[Ammo] || (player_info[Weapon] == 0 && player_info[Firing])){
        auto id = SoundID(KnifeSFX + player_info[Weapon]);
        this->sounds.getSFX(id).play(0);
    }
    last_ammo = player_info[Ammo];
}

