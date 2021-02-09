#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>
#include "../common_src/Configuration.h"
#include "../common_src/Map.h"
#include "Weapons/Weapons.h"

#define HUD_INFO_SIZE 13

class Weapon;
class HealthRecover;
class Treasure;
class Player;

class PlayerActions {
private:
    uint8_t initialHealth;
    int initialBullets;

	uint8_t health, lives;
    int score;
    bool hasKey;
    Weapons weapons;
    int bullets;
    int bulletsCounter;
    int killsCounter;

public:
    /* Constructor */
	PlayerActions(const Configuration& config);
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
	bool hasWeapon(int id) const;
	void equip(Weapon* machine_gun);

	void die();
	bool isDead() const;

    int getKills();
    int getScore();
    int getBulletsFired();

	void startShooting();
	void stopShooting();

	void nextWeapon();
	void prevWeapon();

	bool isShooting() const;
	void fireTheGun(std::vector<Player*>& players,
					uint8_t shooting_player_number,	const Map& map);

    void receiveShot(uint8_t damage);
    void increaseBulletCounter(uint8_t bulletsAmount);
    void increaseKillCounter();
    void useBullets(uint8_t bulletsAmount);
    bool hasBullets();

    /* Escribe los primeros 12 bytes del buffer con la informacion del HUD del
     * jugador de la siguiente manera (respetando el tamanio en bytes de cada variable):
     * [ lives, health, currentWeapon, hasKey, bullets, score ] */
	void geHUDInfo(uint8_t *msg);

	/* Destructor */
	~PlayerActions();
};

#endif
