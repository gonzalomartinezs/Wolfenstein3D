#ifndef WOLFENSTEIN3D_CHAINGUN_H
#define WOLFENSTEIN3D_CHAINGUN_H

#include "Weapon.h"
#include "../../common_src/Timer.h"

#include <vector>

class ChainGun : public Weapon {
private:
    Timer fireTimer;
    float lastShotDelay;
   	const float TIME_BETWEEN_SHOTS;

public:
    /* Constructor */
    ChainGun(const float time_between_shots, float item_radius);

    void startShooting() override;

    void fireTheGun(std::vector<Player*> &players, int shootingPlayerNumber,
                    const Map &map) override;

	Item* getWeaponItem(float x, float y) override;

    /* Destructor */
    ~ChainGun();
};

#endif //WOLFENSTEIN3D_CHAINGUN_H
