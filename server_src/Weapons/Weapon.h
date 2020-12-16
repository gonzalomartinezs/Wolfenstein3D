#ifndef WOLFENSTEIN3D_WEAPON_H
#define WOLFENSTEIN3D_WEAPON_H

#include "../Player.h"
#include <vector>
#include <random>

class Player;

class Weapon {
protected:
    bool isShooting;
    std::random_device rd;

public:
    /* Constructor */
    Weapon();

    virtual void startShooting(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) = 0;

    /* Logica de disparar una sola bala */
    void shoot(std::vector<Player>& players, int shootingPlayerNumber, const Map& map);

    virtual void stopShooting() = 0;

    /* Destructor */
    virtual ~Weapon();

//private:
    bool _isShootable(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map);
    float _angleProbabilityFunction(float angle);
    float _distanceProbabilityFunction(float distance);
    bool _runProbability(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo);

    /* Este metodo es equivalente a una distribucion uniforme [0,1] */
    float _randomNumberGenerator();
};

#endif  // WOLFENSTEIN3D_WEAPON_H
