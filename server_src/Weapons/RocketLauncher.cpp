#include "RocketLauncher.h"

#define BULLETS_PER_ROCKET 5

RocketLauncher::RocketLauncher(std::vector<Rocket>& rockets, float item_radius)
                            : Weapon(ROCKET_LAUNCHER, item_radius),
                               rockets(rockets) {}

void RocketLauncher::startShooting() {
    this->weaponIsShooting = true;
}

void RocketLauncher::fireTheGun(std::vector<Player*>& players,
                                int shootingPlayerNumber, const Map& map) {
    if (players[shootingPlayerNumber]->hasBullets(BULLETS_PER_ROCKET)) {
        players[shootingPlayerNumber]->\
                                    increaseBulletCounter(BULLETS_PER_ROCKET);
        players[shootingPlayerNumber]->useBullets(BULLETS_PER_ROCKET);

        this->rockets.emplace_back(players[shootingPlayerNumber]->getX(),
                                   players[shootingPlayerNumber]->getY(),
                                   players[shootingPlayerNumber]->getDirX(),
                                   players[shootingPlayerNumber]->getDirY(),
                                   shootingPlayerNumber);
    }
    this->weaponIsShooting = false;
}

RocketLauncher::~RocketLauncher() {}
