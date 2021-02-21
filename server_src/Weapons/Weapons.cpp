#include "Weapons.h"
#include <iostream>
#include "Knife.h"
#include "Pistol.h"
#include "ChainGun.h"
#include "MachineGun.h"
#include "../../common_src/BulletItem.h"

#define KEY_INITIAL_WEAPON "initial_weapon"
#define KEY_KNIFE "knife"
#define KEY_CHAIN_GUN "chain_gun"
#define KEY_MACHINE_GUN "machine_gun"

#define KEY_SHOTS "time_between_shots"
#define KEY_BURSTS "time_between_bursts"
#define KEY_BULLETS "bullets_per_burst"

#define KEY_INITIAL_BULLETS "initial_bullets"
#define KEY_MAX_BULLETS "max_bullets"
#define KEY_BULLET "bullet"
#define KEY_BULLET_TEXTURE "texture"
#define KEY_BULLET_RADIUS "radius"

#define LOST_BULLETS 10

Weapons::Weapons(const Configuration& config) :
				current_weapon(config.getInt(KEY_INITIAL_WEAPON)) {
	this->weapons.push_back(new Knife(Configuration(config, KEY_KNIFE)));
	this->weapons.push_back(new Pistol());

    Configuration config_bullet(config, KEY_BULLET);

    this->initial_bullets = config_bullet.getInt(KEY_INITIAL_BULLETS);
    this->bullets = this->initial_bullets;

    this->max_bullets = config_bullet.getInt(KEY_MAX_BULLETS);
    this->bullet_radius = config_bullet.getFloat(KEY_BULLET_RADIUS);
}

bool Weapons::hasWeapon(int id) const {
	for (size_t i = 2; i < this->weapons.size(); ++i) {
		if ((*weapons[i]) == id) return true;
	}

	return false;
}

void Weapons::equip(Weapon* weapon) {
	this->weapons.push_back(weapon);
}

void Weapons::equip(BulletItem* bullet) {
    this->bullets = (*bullet) + this->bullets;
}

void Weapons::nextWeapon() {
    ++(this->current_weapon);
    if (this->current_weapon >= this->weapons.size()) {
        this->current_weapon = 0;
    }
}

void Weapons::prevWeapon() {
    if (this->current_weapon == 0) {
        this->current_weapon = this->weapons.size()-1;
    } else {
        --(this->current_weapon);
    }
}

void Weapons::startShooting() {
    this->weapons[this->current_weapon]->startShooting();
}

void Weapons::stopShooting() {
    this->weapons[this->current_weapon]->stopShooting();
}

bool Weapons::isShooting() const {
    return this->weapons[this->current_weapon]->isShooting();
}

void Weapons::useBullets(uint8_t bullets_amount) {
    this->bullets -= bullets_amount;
}

void Weapons::fireTheGun(std::vector<Player*>& players,
                        int shooting_player_number, const Map& map) {
    this->weapons[this->current_weapon]->fireTheGun(players,
    											shooting_player_number,
                                            	map);
}

void Weapons::reset(Items* items, RandomPosition& rd_pos) {
    this->bullets = this->initial_bullets;
    this->current_weapon = 1;

    while (this->weapons.size() > 2) {
        try {
            items->push_back(weapons.back()->\
                            getWeaponItem(rd_pos.getX(), rd_pos.getY()));
            delete this->weapons.back();
            this->weapons.pop_back();
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    items->push_back(new BulletItem(rd_pos.getX(), rd_pos.getY(),
                                    LOST_BULLETS, this->bullet_radius,
                                    this->max_bullets));
}

bool Weapons::hasBullets(uint8_t bulletsAmount) const {
    return (this->bullets >= bulletsAmount);
}

uint8_t Weapons::getWeaponID() const {
	return this->weapons[this->current_weapon]->getWeaponID();
}

int Weapons::getBullets() const {
    return this->bullets;
}

Weapons::~Weapons() {
	for (size_t i = 0; i < this->weapons.size(); ++i) {
        delete this->weapons[i];
    }
}
