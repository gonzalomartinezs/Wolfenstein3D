#include "ChainGun.h"

#define TIME_BETWEEN_SHOTS 0.1

ChainGun::ChainGun() : Weapon(CHAIN_GUN) {}

void ChainGun::startShooting() {
    this->weaponIsShooting = true;
    this->lastShotDelay = -1;
    this->fireTimer.start();
}

void ChainGun::fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) {
    if (this->lastShotDelay == -1) {
        this->shoot(players, shootingPlayerNumber, map);  /* First shot */
        this->lastShotDelay = 0;

    } else if ((this->fireTimer.getTime()/1000) + this->lastShotDelay >= TIME_BETWEEN_SHOTS ) {
        this->shoot(players, shootingPlayerNumber, map);
        this->lastShotDelay = this->lastShotDelay + (this->fireTimer.getTime()/1000) - TIME_BETWEEN_SHOTS;
        this->fireTimer.start();
    }
}

ChainGun::~ChainGun() {}
