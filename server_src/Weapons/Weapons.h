#ifndef WEAPONS_H
#define WEAPONS_H

#include "../../common_src/Map.h"
#include "../../common_src/Configuration.h"
#include <vector>

class Weapon;
class Player;

class Weapons {
private:
	std::vector<Weapon*> weapons;
	uint8_t current_weapon;
public:
	Weapons(const Configuration& config);
	bool hasWeapon(int id) const;
	void equip(Weapon* weapon);
	void nextWeapon();
	void prevWeapon();
	void startShooting();
	void stopShooting();
	bool isShooting() const;
	void fireTheGun(std::vector<Player*>& players,
                    int shooting_player_number, const Map& map);

	uint8_t getCurrentWeapon() const;
	~Weapons();
};

#endif
