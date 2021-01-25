#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include "Weapons/Weapon.h"
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
    this->currentWeapon = config.getInt(KEY_INITIAL_WEAPON);
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
    memcpy(msg + 2 * sizeof(uint8_t), &this->currentWeapon, sizeof(uint8_t));
    memcpy(msg + 3 * sizeof(uint8_t), &this->hasKey, sizeof(bool));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool), &this->bullets, sizeof(int));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool) + sizeof(int), &this->score, sizeof(int));

}

PlayerActions::~PlayerActions() {}