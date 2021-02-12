#include "Weapons.h"
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

Weapons::Weapons(const Configuration& config) :
				current_weapon(config.getInt(KEY_INITIAL_WEAPON)),
                initial_bullets(config.getInt(KEY_INITIAL_BULLETS)),
                bullets(config.getInt(KEY_INITIAL_BULLETS)) { 
	this->weapons.push_back(new Knife(Configuration(config, KEY_KNIFE)));
	this->weapons.push_back(new Pistol());

    //Solo para test
/*    Configuration config_chain_gun(config, KEY_CHAIN_GUN);
	this->weapons.push_back(
                    new ChainGun(config_chain_gun.getFloat(KEY_SHOTS)));

    Configuration config_machine_gun(config, KEY_MACHINE_GUN);
	this->weapons.push_back(new MachineGun(
                                    config_machine_gun.getFloat(KEY_SHOTS),
                                    config_machine_gun.getFloat(KEY_BURSTS),
                                    config_machine_gun.getInt(KEY_BULLETS)));*/
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

uint8_t Weapons::getCurrentWeapon() const {
	return this->current_weapon;
}

bool Weapons::hasBullets() const {
    return (this->bullets > 0);
}

int Weapons::getBullets() const {
    return this->bullets;
}

Weapons::~Weapons() {
	for (size_t i = 0; i < this->weapons.size(); ++i) {
        delete this->weapons[i];
    }
}