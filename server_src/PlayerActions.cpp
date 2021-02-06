#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include <cstring>

#define KEY_INITIAL_HEALTH "initial_health"
#define KEY_INITIAL_SCORE "initial_score"
#define KEY_TOTAL_LIVES "total_lives"
#define KEY_HAS_KEY "has_key"
#define KEY_INITIAL_BULLETS "initial_bullets"
#define KEY_WEAPONS "weapons"

PlayerActions::PlayerActions(const Configuration& config) :
                            weapons(Configuration(config, KEY_WEAPONS)) {
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
	return this->weapons.hasWeapon(id);
}

void PlayerActions::equip(Weapon* weapon) {
	this->weapons.equip(weapon);
}

bool PlayerActions::isDead() const {
	return (this->health <= 0);
}

void PlayerActions::startShooting() {
    this->weapons.startShooting();
}

void PlayerActions::stopShooting() {
    this->weapons.stopShooting();
}

void PlayerActions::nextWeapon() {
    this->weapons.nextWeapon();
}

void PlayerActions::prevWeapon() {
    this->weapons.prevWeapon();
}

bool PlayerActions::isShooting() const {
    return this->weapons.isShooting();
}

void PlayerActions::fireTheGun(std::vector<Player*>& players,
                            uint8_t shooting_player_number, const Map& map) {
    this->weapons.fireTheGun(players, shooting_player_number,
                                            map);
}

void PlayerActions::receiveShot(uint8_t damage) {
    this->health -= damage;
    /* uint8_t no admite valores negativos */
    if (this->health > 100) {
        this->health = 0;
        //this->die();
    }
}

void PlayerActions::geHUDInfo(uint8_t* msg) {
    memcpy(msg, &this->lives, sizeof(uint8_t));
    memcpy(msg + sizeof(uint8_t), &this->health, sizeof(uint8_t));

    uint8_t current_weapon = this->weapons.getCurrentWeapon();
    memcpy(msg + 2 * sizeof(uint8_t), &current_weapon, sizeof(uint8_t));
    memcpy(msg + 3 * sizeof(uint8_t), &this->hasKey, sizeof(bool));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool), &this->bullets, sizeof(int));
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool) + sizeof(int), &this->score, sizeof(int));

}

PlayerActions::~PlayerActions() {}