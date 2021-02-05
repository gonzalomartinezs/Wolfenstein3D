#ifndef WOLFENSTEIN3D_CHAINGUN_H
#define WOLFENSTEIN3D_CHAINGUN_H

#include "Weapon.h"
#include "../../common_src/Timer.h"

class ChainGun : public Weapon {
private:
    Timer fireTimer;
    float lastShotDelay;
   	const float TIME_BETWEEN_SHOTS;

public:
    /* Constructor */
    ChainGun(const float time_between_shots);

    void startShooting() override;

    void fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) override;

    /* Destructor */
    ~ChainGun();
};

#endif //WOLFENSTEIN3D_CHAINGUN_H
