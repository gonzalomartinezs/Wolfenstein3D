#include "Pistol.h"

Pistol::Pistol() {}

void Pistol::startShooting() {
    this->shoot(/* Argumentos */);
    this->stopShooting()
}

void Pistol::stopShooting() {
    this->isShooting = false;
}

Pistol::~Pistol() {}