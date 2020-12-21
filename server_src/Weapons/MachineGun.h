#ifndef WOLFENSTEIN_MACHINEGUN_H
#define WOLFENSTEIN_MACHINEGUN_H

#include "Weapon.h"
#include "../../common_src/Timer.h"

class MachineGun : public Weapon {
private:
    Timer fireTimer;
    Timer burstTimer;
    float lastShotDelay;
    int burstBulletCounter;
    bool isInBurstRecover;
    bool isFirstBulletOfTheBurst;

public:
    /* Constructor */
    MachineGun();

    void startShooting() override;

    void fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) override;

    /* Destructor */
    ~MachineGun();
};

#endif  // WOLFENSTEIN_MACHINEGUN_H
