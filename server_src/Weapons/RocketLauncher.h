#ifndef WOLFENSTEIN3D_ROCKETLAUNCHER_H_
#define WOLFENSTEIN3D_ROCKETLAUNCHER_H_

#include "Weapon.h"
#include "Rocket.h"

class RocketLauncher : public Weapon {
private:
    std::vector<Rocket>& rockets;
public:
    /* Constructor */
    RocketLauncher(std::vector<Rocket>& rockets, float item_radius);

    void startShooting() override;

    void fireTheGun(std::vector<Player*>& players, int shootingPlayerNumber,
    				const Map& map) override;

    /* Destructor */
    ~RocketLauncher();
};

#endif //WOLFENSTEIN3D_ROCKETLAUNCHER_H_
