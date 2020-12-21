#include "Pistol.h"

Pistol::Pistol() : Weapon(PISTOL) {}

void Pistol::startShooting() {
    this->weaponIsShooting = true;
}

void Pistol::fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) {
    this->shoot(players, shootingPlayerNumber, map);
    this->weaponIsShooting = false;
}

Pistol::~Pistol() {}