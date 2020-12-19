#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H

#include "../../common_src/Map.h"
#include "../Player.h"
#include <vector>
#include <random>

class Player;

class Weapon {
protected:
    bool weaponIsShooting;
    std::random_device rd;

public:
    /* Constructor */
    Weapon();

    virtual void fireTheGun(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) = 0;

    /* AKA started pulling the trigger */
    virtual void startShooting() = 0;

    /* Return true if the player is pulling the trigger */
    bool isShooting();

    /* Destructor */
    virtual ~Weapon();

protected:
    /* Logica de disparar una sola bala */
    void shoot(std::vector<Player>& players, int shootingPlayerNumber, const Map& map);

private:
    /* Devuelve true si no hay paredes entre los jugadores, en otro caso false */
    bool _isInTheFieldOfView(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map);

    /* Probability decays linearly with the angle */
    float _angleProbabilityFunction(float angle);

    /* Probability decays linearly with the distance */
    float _distanceProbabilityFunction(float distance);

    /* Genera una probabilidad de impacto segun el angulo y la distancia */
    bool _runProbability(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo);

    /* Este metodo es equivalente a una distribucion uniforme [0,1] */
    float _randomNumberGenerator();
};

#endif  // WOLFENSTEIN3D_WEAPON_H
