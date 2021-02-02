#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include "Weapons/Weapon.h"
#include "Weapons/Knife.h"
#include "Weapons/Pistol.h"
#include "Weapons/ChainGun.h"
#include "Weapons/MachineGun.h"
//#include "Weapons/RocketLauncher.h"
#include <cstring>

#define KEY_INITIAL_HEALTH "initial_health"
#define KEY_INITIAL_SCORE "initial_score"
#define KEY_TOTAL_LIVES "total_lives"
#define KEY_HAS_KEY "has_key"
#define KEY_INITIAL_BULLETS "initial_bullets"
#define KEY_INITIAL_WEAPON "initial_weapon"

PlayerActions::PlayerActions(const Configuration& config) {
	this->health = config.getInt(KEY_INITIAL_HEALTH);
    this->score = config.getInt(KEY_INITIAL_SCORE);
    this->lives = config.getInt(KEY_TOTAL_LIVES);
    this->hasKey = config.getInt(KEY_HAS_KEY);
    this->bullets = config.getInt(KEY_INITIAL_BULLETS);
    this->current_weapon = config.getInt(KEY_INITIAL_WEAPON);
    this->weapons.push_back(new Knife());
    this->weapons.push_back(new Pistol());
}

void PlayerActions::use(HealthRecover* recover) {
	this->health = (*recover) + this->health;
}

void PlayerActions::use(Treasure* treasure) {
	this->score = (*treasure) + this->score;
}

bool PlayerActions::hasWeapon(int id) const {
	for (size_t i = 2; i < this->weapons.size(); ++i) {
		if ((*weapons[i]) == id) return false;
	}

	return true;
}

void PlayerActions::equip(Weapon* weapon) {
	this->weapons.push_back(weapon);
}

bool PlayerActions::isDead() const {
	return (this->health <= 0);
}

void PlayerActions::startShooting() {
    this->weapons[this->current_weapon]->startShooting();
}

void PlayerActions::stopShooting() {
    this->weapons[this->current_weapon]->stopShooting();
}

void PlayerActions::nextWeapon() {
    ++(this->current_weapon);
    if (this->current_weapon >= this->weapons.size()) {
        this->current_weapon = 0;
    }
}

void PlayerActions::prevWeapon() {
    --(this->current_weapon);
    if (this->current_weapon <= 0) {
        this->current_weapon = this->weapons.size()-1;
    }
}

bool PlayerActions::isShooting() const {
    return this->weapons[this->current_weapon]->isShooting();
}

void PlayerActions::fireTheGun(std::vector<Player>& players,
                                int shooting_player_number, const Map& map) {
    this->weapons[current_weapon]->fireTheGun(players, shooting_player_number,
                                            map);
}

void PlayerActions::receiveShot(uint8_t damage) {
    this->health -= damage;
    if (this->health <= 20) {
        this->health = 100;
        //this->die();
    }
}

void PlayerActions::geHUDInfo(uint8_t* msg) {
    memcpy(msg, &this->lives, sizeof(uint8_t));
    memcpy(msg + sizeof(uint8_t), &this->health, sizeof(uint8_t));
    memcpy(msg + 2 * sizeof(uint8_t), &this->current_weapon, sizeof(uint8_t));
    memcpy(msg + 3 * sizeof(uint8_t), &this->hasKey, sizeof(bool));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool), &this->bullets, sizeof(int));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool) + sizeof(int), &this->score, sizeof(int));

}

PlayerActions::~PlayerActions() {
    for (size_t i = 0; i < this->weapons.size(); ++i) {
        delete (this->weapons[i]);
    }
}