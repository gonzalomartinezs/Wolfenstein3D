#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>
#include "../common_src/Configuration.h"
#include "../common_src/Map.h"
#include "../common_src/ManualDoor.h"
#include "Weapons/Weapons.h"
#include "Key.h"

#define HUD_INFO_SIZE 13

class Weapon;
class HealthRecover;
class Treasure;
class BulletItem;
class Items;
class Player;

class PlayerActions {
private:
    uint8_t initialHealth;
	uint8_t health, lives;
    int score;
    Key key;
    Weapons weapons;
    int bulletsCounter;
    int killsCounter;
    bool hasLost;

public:
    /* Constructor */
	explicit PlayerActions(const Configuration& config);
	void use(HealthRecover* recover);
	void use(Treasure* treasure);
    void use(BulletItem* bullet);
	bool hasWeapon(int id) const;
	void equip(Weapon* machine_gun);
	void equipKey();
	bool hasKey() const;
	void interactWith(ManualDoor& door);

	uint8_t getWeaponID() const;

	void die(Items* items, float x, float y);
	bool isDead() const;
	bool playerHasLost();

    int getKills();
    int getScore();
    int getBulletsFired();

	void startShooting();
	void stopShooting();

	void nextWeapon();
	void prevWeapon();
	void setWeapon(uint8_t id);

	bool isShooting() const;
	void fireTheGun(std::vector<Player*>& players,
					uint8_t shooting_player_number,	const Map& map);

    void receiveShot(uint8_t damage);
    void increaseBulletCounter(uint8_t bulletsAmount);
    void increaseKillCounter();
    void useBullets(uint8_t bulletsAmount);
    bool hasBullets(uint8_t bulletsAmount);

    /* Escribe los primeros 12 bytes del buffer con la informacion del HUD del
     * jugador de la siguiente manera (respetando el tamanio en bytes de cada variable):
     * [ lives, health, currentWeapon, hasKey, bullets, score ] */
	void getHUDInfo(uint8_t *msg);

	/* Destructor */
	~PlayerActions();
};

#endif
