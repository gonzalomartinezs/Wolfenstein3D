#ifndef WOLFENSTEIN3D_PISTOL_H
#define WOLFENSTEIN3D_PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon {
public:
    /* Constructor */
    Pistol();

    /* AKA started pulling the trigger */
    void startShooting(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) override;

    /* AKA stopped pulling the trigger */
    void stopShooting() override;

    /* Destructor */
    ~Pistol();
};

#endif  // WOLFENSTEIN3D_PISTOL_H
