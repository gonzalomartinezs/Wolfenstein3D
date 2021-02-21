#ifndef WOLFENSTEIN3D_ROCKET_H_
#define WOLFENSTEIN3D_ROCKET_H_

#include <vector>
#include "../../common_src/DirectedPositionable.h"
#include "../../common_src/Map.h"
#include "../../common_src/Collider.h"

class Player;

class Rocket : public DirectedPositionable {
private:
    float MOVE_SPEED, SIZE, MAX_DAMAGE, MAX_DAMAGE_DISTANCE;
    int shootingPlayerNumber;
    bool exploded;

public:
    /* Constructor */
    Rocket(float _move_speed, float _size, float _max_damage,
        float _max_damage_distance, float pos_x, float pos_y,
        float dir_x, float dir_y, int shootingPlayerNumber);

    /* Actualiza el estado del Rocket (Step-Time) */
    void update(std::vector<Player*>& players, const Map& map);

    /* Devuelve true si el Rocket explotó */
    bool hasExploded() const;

    /* Escribe los primeros 16 bytes del buffer con la informacion de
     * la posicion del jugador de la siguiente manera (floats):
     * [ posX, posY, dirX, dirY ] */
    void getPositionData(uint8_t *msg);

    /* Destructor */
    ~Rocket();

private:
    /* Inflige el daño correspondiente a cada uno de los jugadores cercanos */
    void _explode(std::vector<Player*>& players, const Map& map);

    /* Calcula el daño en base a la distancia */
    uint8_t _calculateDamage(float distance);

    /* Devuelve true si detecta algún tipo de colision */
    bool _collided(std::vector<Player*>& players, const Map& map);

    /* Devuelve true si el Rocket esta en colisión con algún jugador que no
     * sea el que creo el Rocket */
    bool _lookForPlayerCollision(std::vector<Player*>& players, const Collider& collider);

    /* Devuelve true si el Rocket esta en colision con alguna pared */
    bool _lookForWallCollision(const Map& map, const Collider& collider);
};

#endif  // WOLFENSTEIN3D_ROCKET_H_
