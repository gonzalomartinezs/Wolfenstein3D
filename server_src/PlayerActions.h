#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>
#include "../common_src/Configuration.h"

class Weapon;
class HealthRecover;
class Treasure;
class WeaponItem;
class MachineGunItem;

class PlayerActions {
private:
	uint8_t health, lives;
    int score;
    bool hasKey;
    std::vector<Weapon*> weapons;
    int bullets;
public:
	PlayerActions(const Configuration& config);
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
	bool hasWeapon(int id) const;
	void equip(Weapon* machine_gun);
	bool isDead() const;
	~PlayerActions();
};

#endif
