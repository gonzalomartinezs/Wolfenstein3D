#include "Pistol.h"

Pistol::Pistol() {}

void Pistol::startShooting(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) {
    this->shoot(players, shootingPlayerNumber, map);
    this->stopShooting();
}

void Pistol::stopShooting() {
    this->isShooting = false;
}

Pistol::~Pistol() {}