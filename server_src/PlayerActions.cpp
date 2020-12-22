#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include "Weapons/Weapon.h"

#define KEY_INITIAL_HEALTH "initial_health"
#define KEY_INITIAL_SCORE "initial_score"
#define KEY_TOTAL_LIVES "total_lives"
#define KEY_HAS_KEY "has_key"
#define KEY_INITIAL_BULLETS "initial_bullets"

PlayerActions::PlayerActions(const Configuration& config) {
	this->health = config.getInt(KEY_INITIAL_HEALTH);
    this->score = config.getInt(KEY_INITIAL_SCORE);
    this->lives = config.getInt(KEY_TOTAL_LIVES);
    this->hasKey = config.getInt(KEY_HAS_KEY);
    this->bullets = config.getInt(KEY_INITIAL_BULLETS);
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

PlayerActions::~PlayerActions() {}