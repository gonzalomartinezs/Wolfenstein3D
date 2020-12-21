#include "MachineGun.h"

#define TIME_BETWEEN_SHOTS 0.1
#define TIME_BETWEEN_BURSTS 0.3
#define BULLETS_PER_BURST 5

MachineGun::MachineGun() : Weapon(MACHINE_GUN) {}

void MachineGun::startShooting() {
    this->weaponIsShooting = true;
    this->lastShotDelay = -1;
    this->burstBulletCounter = 0;
    this->isInBurstRecover = false;
    this->fireTimer.start();
}

void MachineGun::fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) {
    if (this->lastShotDelay == -1) {
        this->shoot(players, shootingPlayerNumber, map);  /* First shot */
        this->burstBulletCounter++;
        this->lastShotDelay = 0;

    } else if (((this->fireTimer.getTime()/1000) + this->lastShotDelay >= TIME_BETWEEN_SHOTS) &&
                (this->burstBulletCounter < BULLETS_PER_BURST) && (this->isInBurstRecover == false)) {
        this->shoot(players, shootingPlayerNumber, map);
        this->lastShotDelay = this->lastShotDelay + (this->fireTimer.getTime()/1000) - TIME_BETWEEN_SHOTS;
        this->burstBulletCounter++;
        this->fireTimer.start();
    }

    if (this->burstBulletCounter >= BULLETS_PER_BURST) {
        this->burstTimer.start();
        this->burstBulletCounter = 0;
        this->isInBurstRecover = true;

    } else if (this->isInBurstRecover && ((this->burstTimer.getTime()/1000) > TIME_BETWEEN_BURSTS)) {
        this->isInBurstRecover = false;
        this->fireTimer.start();  /* Si bien no disparo empiezo a contar aca */
    }
}

MachineGun::~MachineGun() {}
