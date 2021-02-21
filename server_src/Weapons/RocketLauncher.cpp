#include "RocketLauncher.h"

#define BULLETS_PER_ROCKET 5

RocketLauncher::RocketLauncher(float rocket_move_speed, float rocket_size,
          float rocket_max_damage, float rocket_max_damage_distance,
          std::vector<Rocket>& rockets, float item_radius)
          : Weapon(ROCKET_LAUNCHER, item_radius), rockets(rockets),
          ROCKET_MOVE_SPEED(rocket_move_speed),
          ROCKET_SIZE(rocket_size), ROCKET_MAX_DAMAGE(rocket_max_damage),
        ROCKET_MAX_DAMAGE_DISTANCE(rocket_max_damage_distance) {}

void RocketLauncher::startShooting() {
    this->weaponIsShooting = true;
}

void RocketLauncher::fireTheGun(std::vector<Player*>& players,
                                int shootingPlayerNumber, const Map& map) {
    if (players[shootingPlayerNumber]->hasBullets(BULLETS_PER_ROCKET)) {
        players[shootingPlayerNumber]->\
                                    increaseBulletCounter(BULLETS_PER_ROCKET);
        players[shootingPlayerNumber]->useBullets(BULLETS_PER_ROCKET);

        this->rockets.emplace_back(this->ROCKET_MOVE_SPEED, this->ROCKET_SIZE,
                                  this->ROCKET_MAX_DAMAGE,
                                  this->ROCKET_MAX_DAMAGE_DISTANCE,
                                  players[shootingPlayerNumber]->getX(),
                                  players[shootingPlayerNumber]->getY(),
                                  players[shootingPlayerNumber]->getDirX(),
                                  players[shootingPlayerNumber]->getDirY(),
                                  shootingPlayerNumber);
    }
    this->weaponIsShooting = false;
}

RocketLauncher::~RocketLauncher() {}
