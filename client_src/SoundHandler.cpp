#include "SoundHandler.h"
#include "sound/SoundID.h"

#define FOREVER -1

SoundHandler::SoundHandler(SoundsContainer &sounds): sounds(sounds), last_ammo(0){}

void SoundHandler::startBackMusic() {
    this->sounds.getMusic(BackMusic).play(FOREVER);
}

SoundHandler::~SoundHandler() {}

