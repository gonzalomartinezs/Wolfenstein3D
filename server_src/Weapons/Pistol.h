#ifndef WOLFENSTEIN3D_PISTOL_H
#define WOLFENSTEIN3D_PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon {
public:
    /* Constructor */
    Pistol();

    void startShooting() override;

    void fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) override;

    /* Destructor */
    ~Pistol();
};

#endif  // WOLFENSTEIN3D_PISTOL_H
