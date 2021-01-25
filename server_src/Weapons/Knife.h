#ifndef WOLFENSTEIN3D_KNIFE_H
#define WOLFENSTEIN3D_KNIFE_H

#include "Weapon.h"

class Knife : public Weapon {
public:
    /* Constructor */
    Knife();

    void startShooting() override;

    void fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) override;

    /* Destructor */
    ~Knife();

private:
    bool _isInTheKnifeRange(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo);
};

#endif //WOLFENSTEIN3D_KNIFE_H
