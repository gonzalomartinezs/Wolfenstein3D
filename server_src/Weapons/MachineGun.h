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
    const float TIME_BETWEEN_SHOTS, TIME_BETWEEN_BURSTS;
    const int BULLETS_PER_BURST;

public:
    /* Constructor */
    MachineGun(const float time_between_shots,
                const float time_between_bursts,
                const int bullets_per_burst);

    void startShooting() override;

    void fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) override;

    /* Destructor */
    ~MachineGun();
};

#endif  // WOLFENSTEIN_MACHINEGUN_H
