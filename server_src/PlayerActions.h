#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>

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
	PlayerActions();
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
	bool hasWeapon(int id) const;
	void equip(Weapon* machine_gun);
	bool isDead() const;
	~PlayerActions();
};

#endif
