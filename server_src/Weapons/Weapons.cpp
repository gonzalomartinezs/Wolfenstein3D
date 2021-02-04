#include "Weapons.h"
#include "Knife.h"
#include "Pistol.h"
#include "ChainGun.h"

Weapons::Weapons() : current_weapon(2) {
	this->weapons.push_back(new Knife());
	this->weapons.push_back(new Pistol());
	this->weapons.push_back(new ChainGun());
}
/*
Weapons::Weapons(Weapons&& other) {
	this->weapons.swap(other.weapons);
	this->current_weapon = other.current_weapon;
}

Weapons&& Weapons::operator=(Weapons&& other) {
	this->weapons.swap(other.weapons);
	this->current_weapon = other.current_weapon;	
}
*/
bool Weapons::hasWeapon(int id) const {
	for (size_t i = 2; i < this->weapons.size(); ++i) {
		if ((*weapons[i]) == id) return false;
	}

	return true;
}

void Weapons::equip(Weapon* weapon) {
	this->weapons.push_back(weapon);
}

void Weapons::nextWeapon() {
    ++(this->current_weapon);
    if (this->current_weapon >= this->weapons.size()) {
        this->current_weapon = 0;
    }
}

void Weapons::prevWeapon() {
    --(this->current_weapon);
    if (this->current_weapon <= 0) {
        this->current_weapon = this->weapons.size()-1;
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

void Weapons::fireTheGun(std::vector<Player>& players,
                        int shooting_player_number, const Map& map) {
    this->weapons[this->current_weapon]->fireTheGun(players,
    											shooting_player_number,
                                            	map);
}

Weapons::~Weapons() {
	for (size_t i = 0; i < this->weapons.size(); ++i) {
        delete this->weapons[i];
    }
}