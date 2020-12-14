#include "PlayerAttributes.h"

#define MAX_HEALTH 100
#define INITIAL_SCORE 0
#define TOTAL_LIVES 3

PlayerAttributes::PlayerAttributes() {
    this->health = MAX_HEALTH;
    this->score = INITIAL_SCORE;
    this->lives = TOTAL_LIVES;
    this->hasKey = false;
}

void PlayerAttributes::addHealth(int _health) {
	this->health += _health;
}

bool PlayerAttributes::isDead() const {
	return (this->health <= 0);
}

PlayerAttributes::~PlayerAttributes() {}