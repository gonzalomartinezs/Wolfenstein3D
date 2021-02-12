#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H

#include "../../common_src/Map.h"
#include "../Player.h"
#include <vector>
#include <random>

enum WEAPON_ID{KNIFE = 0, PISTOL = 1, MACHINE_GUN = 2, CHAIN_GUN = 3, ROCKET_LAUNCHER = 4};

class Player;

class Weapon {
protected:
    bool weaponIsShooting;
    std::random_device rd;
    int id;

public:
    /* Constructor */
    Weapon(int _id);

    virtual void fireTheGun(std::vector<Player*>& players, int shootingPlayerNumber, const Map& map) = 0;

    /* AKA started pulling the trigger */
    virtual void startShooting() = 0;

    /* AKA stopped pulling the trigger */
    void stopShooting();

    /* Return true if the player is pulling the trigger */
    bool isShooting();

    bool operator==(int other_id) const;

    /* Destructor */
    virtual ~Weapon();

protected:
    /* Logica de disparar una sola bala */
    void shoot(std::vector<Player*>& players, int shootingPlayerNumber, const Map& map);

    /* Este metodo es equivalente a una distribucion uniforme [0,1] */
    float _randomNumberGenerator();

private:
    /* Devuelve true si no hay paredes entre los jugadores, en otro caso false */
    bool _isInTheFieldOfView(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map);

    /* Probability decays linearly with the angle */
    float _angleProbabilityFunction(float angle);

    /* Probability decays linearly with the distance */
    float _distanceProbabilityFunction(float distance);

    /* Genera una probabilidad de impacto segun el angulo y la distancia */
    bool _runProbability(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo);
};

#endif  // WOLFENSTEIN3D_WEAPON_H
