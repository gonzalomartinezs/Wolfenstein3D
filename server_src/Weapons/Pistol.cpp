#include "Pistol.h"
#include <vector>

Pistol::Pistol() : Weapon(PISTOL) {}

void Pistol::startShooting() {
    this->weaponIsShooting = true;
}

void Pistol::fireTheGun(std::vector<Player*> &players,
						int shootingPlayerNumber, const Map &map) {
    this->shoot(players, shootingPlayerNumber, map);
    players[shootingPlayerNumber]->makeSound(PistolSFX);
    this->weaponIsShooting = false;
}

Pistol::~Pistol() {}
