#ifndef WEAPONS_H
#define WEAPONS_H

#include "../../common_src/Map.h"
#include "../../common_src/Configuration.h"
#include <vector>

class Weapon;
class Player;
class BulletItem;

class Weapons {
private:
	std::vector<Weapon*> weapons;
	uint8_t current_weapon;
	int initial_bullets, bullets;
public:
	Weapons(const Configuration& config);
	bool hasWeapon(int id) const;
	void equip(Weapon* weapon);
	void equip(BulletItem* bullet);
	void nextWeapon();
	void prevWeapon();
	void startShooting();
	void stopShooting();
	bool isShooting() const;
	void useBullets(uint8_t bullets_amount);
	void fireTheGun(std::vector<Player*>& players,
                    int shooting_player_number, const Map& map);
	bool hasBullets() const;
	uint8_t getCurrentWeapon() const;
	int getBullets() const;
	~Weapons();
};

#endif
