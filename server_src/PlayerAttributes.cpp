#include "PlayerAttributes.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"

#define MAX_HEALTH 100
#define INITIAL_SCORE 0
#define TOTAL_LIVES 3

PlayerAttributes::PlayerAttributes() {
    this->health = MAX_HEALTH;
    this->score = INITIAL_SCORE;
    this->lives = TOTAL_LIVES;
    this->hasKey = false;
}

void PlayerAttributes::use(HealthRecover* recover) {
	this->health = (*recover) + this->health;
}

void PlayerAttributes::use(Treasure* treasure) {
	this->score = (*treasure) + this->score;
}

bool PlayerAttributes::isDead() const {
	return (this->health <= 0);
}

PlayerAttributes::~PlayerAttributes() {}