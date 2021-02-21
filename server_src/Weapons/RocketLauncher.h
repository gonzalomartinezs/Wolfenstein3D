#ifndef WOLFENSTEIN3D_ROCKETLAUNCHER_H_
#define WOLFENSTEIN3D_ROCKETLAUNCHER_H_

#include "Weapon.h"
#include "Rocket.h"

class RocketLauncher : public Weapon {
private:
    std::vector<Rocket>& rockets;
    const float ROCKET_MOVE_SPEED, ROCKET_SIZE, ROCKET_MAX_DAMAGE,
				ROCKET_MAX_DAMAGE_DISTANCE; 
public:
    /* Constructor */
    RocketLauncher(float rocket_move_speed, float rocket_size,
    			float rocket_max_damage, float rocket_max_damage_distance,
    			std::vector<Rocket>& rockets, float item_radius);

    void startShooting() override;

    void fireTheGun(std::vector<Player*>& players, int shootingPlayerNumber,
    				const Map& map) override;

    /* Destructor */
    ~RocketLauncher();
};

#endif //WOLFENSTEIN3D_ROCKETLAUNCHER_H_
