#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include "Weapons/Weapon.h"

#define MAX_HEALTH 100
#define INITIAL_SCORE 0
#define TOTAL_LIVES 3
#define INITIAL_BULLETS 10

PlayerActions::PlayerActions() {
    this->health = MAX_HEALTH;
    this->score = INITIAL_SCORE;
    this->lives = TOTAL_LIVES;
    this->hasKey = false;
    this->bullets = INITIAL_BULLETS;
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