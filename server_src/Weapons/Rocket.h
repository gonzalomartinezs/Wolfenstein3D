#ifndef WOLFENSTEIN3D_ROCKET_H_
#define WOLFENSTEIN3D_ROCKET_H_

#include <vector>
#include "../../common_src/DirectedPositionable.h"
#include "../../common_src/Map.h"
#include "../../common_src/Collider.h"

class Player;


class Rocket : public DirectedPositionable {
private:
    float moveSpeed;
    int shootingPlayerNumber;
    bool exploded;

public:
    /* Constructor */
    Rocket(float pos_x, float pos_y, float dir_x, float dir_y, int shootingPlayerNumber);

    void update(std::vector<Player*>& players, const Map& map);

    bool hasExploded();

    /* Destructor */
    ~Rocket();

private:
    void _explode(std::vector<Player*>& players, const Map& map);
    uint8_t _calculateDamage(float distance);
    bool _collided(std::vector<Player*>& players, const Map& map);
    bool _lookForPlayerCollision(std::vector<Player*>& players, const Collider& collider);
    bool _lookForWallCollision(const Map& map, const Collider& collider);
};

#endif  // WOLFENSTEIN3D_ROCKET_H_
