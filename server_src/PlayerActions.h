#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>
#include "../common_src/Configuration.h"

#define HUD_INFO_SIZE 12

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
    uint8_t currentWeapon;
    std::vector<Weapon*> weapons;
    int bullets;
public:
    /* Constructor */
	PlayerActions(const Configuration& config);
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
	bool hasWeapon(int id) const;
	void equip(Weapon* machine_gun);
	bool isDead() const;

    /* Escribe los primeros 12 bytes del buffer con la informacion del HUD del
     * jugador de la siguiente manera (respetando el tamanio en bytes de cada variable):
     * [ lives, health, currentWeapon, hasKey, bullets, score ] */
	void geHUDInfo(uint8_t *msg);

	/* Destructor */
	~PlayerActions();
};

#endif
