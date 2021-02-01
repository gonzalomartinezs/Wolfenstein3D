#ifndef PLAYERACTIONS_H
#define PLAYERACTIONS_H

#include <cstdint>
#include <vector>
#include "../common_src/Configuration.h"
#include "../common_src/Map.h"

#define HUD_INFO_SIZE 12

class Weapon;
class HealthRecover;
class Treasure;
class Player;

class PlayerActions {
private:
	uint8_t health, lives;
    int score;
    bool hasKey;
    uint8_t current_weapon;
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

	void startShooting();
	void stopShooting();

	void nextWeapon();
	void prevWeapon();

	bool isShooting() const;
	void fireTheGun(std::vector<Player>& players, int shooting_player_number,
					const Map& map);

    void receiveShot(uint8_t damage);

    /* Escribe los primeros 12 bytes del buffer con la informacion del HUD del
     * jugador de la siguiente manera (respetando el tamanio en bytes de cada variable):
     * [ lives, health, currentWeapon, hasKey, bullets, score ] */
	void geHUDInfo(uint8_t *msg);

	/* Destructor */
	~PlayerActions();
};

#endif
