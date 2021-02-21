#ifndef WEAPONS_H
#define WEAPONS_H

#include "../../common_src/Map.h"
#include "../../common_src/Configuration.h"
#include "../../client_src/textures/TextureID.h"
#include "../RandomPosition.h"
#include <vector>

class Weapon;
class Player;
class BulletItem;
class Items;

class Weapons {
private:
	std::vector<Weapon*> weapons;
	uint8_t current_weapon;
	int initial_bullets, bullets, max_bullets;

	float bullet_radius;

public:
	explicit Weapons(const Configuration& config);
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
	bool hasBullets(uint8_t bulletsAmount) const;
	void reset(Items* items, RandomPosition& rd_pos);
	uint8_t getWeaponID() const;
	int getBullets() const;
	~Weapons();
};

#endif
