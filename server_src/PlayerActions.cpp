#include "PlayerActions.h"
#include "../common_src/HealthRecover.h"
#include "../common_src/Treasure.h"
#include "../common_src/BulletItem.h"
#include <cstring>

#define KEY_INITIAL_HEALTH "initial_health"
#define KEY_INITIAL_SCORE "initial_score"
#define KEY_TOTAL_LIVES "total_lives"
#define KEY_INITIAL_BULLETS "initial_bullets"
#define KEY_WEAPONS "weapons"

PlayerActions::PlayerActions(const Configuration& config) :
                            weapons(Configuration(config, KEY_WEAPONS)) {
	this->health = config.getInt(KEY_INITIAL_HEALTH);
    this->score = config.getInt(KEY_INITIAL_SCORE);
    this->lives = config.getInt(KEY_TOTAL_LIVES);
    this->initialHealth = config.getInt(KEY_INITIAL_HEALTH);
    this->bulletsCounter = 0;
    this->killsCounter = 0;
}

void PlayerActions::use(HealthRecover* recover) {
	this->health = (*recover) + this->health;
}

void PlayerActions::use(Treasure* treasure) {
	this->score = (*treasure) + this->score;
}

void PlayerActions::use(BulletItem* bullet) {
    this->weapons.equip(bullet);
}

bool PlayerActions::hasWeapon(int id) const {
	return this->weapons.hasWeapon(id);
}

void PlayerActions::equip(Weapon* weapon) {
	this->weapons.equip(weapon);
}

void PlayerActions::equip(int key_id) {
    this->keys.push_back(key_id);
}

uint8_t PlayerActions::getCurrentWeapon() {
    return this->weapons.getCurrentWeapon();
}

void PlayerActions::die() {
    this->health = this->initialHealth;
//    this->bullets = this->initialBullets;
    this->lives--;
}

bool PlayerActions::isDead() const {
	return (this->health <= 0);
}

int PlayerActions::getKills() {
    return this->killsCounter;
}

int PlayerActions::getScore() {
    return this->score;
}

int PlayerActions::getBulletsFired() {
    return this->bulletsCounter;
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
    }
}

void PlayerActions::increaseBulletCounter(uint8_t bulletsAmount) {
    this->bulletsCounter += bulletsAmount;
}

void PlayerActions::increaseKillCounter() {
    this->killsCounter++;
}

void PlayerActions::useBullets(uint8_t bulletsAmount) {
    this->weapons.useBullets(bulletsAmount);
}

bool PlayerActions::hasBullets() {
    return this->weapons.hasBullets();
}

void PlayerActions::geHUDInfo(uint8_t* msg) {
    memcpy(msg, &this->lives, sizeof(uint8_t));
    memcpy(msg + sizeof(uint8_t), &this->health, sizeof(uint8_t));

    uint8_t current_weapon = this->weapons.getCurrentWeapon();
    memcpy(msg + 2 * sizeof(uint8_t), &current_weapon, sizeof(uint8_t));

    bool has_key = !(this->keys.empty());
    memcpy(msg + 3 * sizeof(uint8_t), &(has_key), sizeof(bool));

    uint8_t weapon_is_shooting = this->weapons.isShooting();
    memcpy(msg + 3 * sizeof(uint8_t) + sizeof(bool), &weapon_is_shooting, sizeof(bool));

    int bullets = this->weapons.getBullets();
    memcpy(msg + 3 * sizeof(uint8_t) + 2 * sizeof(bool), &bullets, sizeof(int));
    memcpy(msg + 3 * sizeof(uint8_t) + 2 * sizeof(bool) + sizeof(int), &this->score, sizeof(int));

}

PlayerActions::~PlayerActions() {}