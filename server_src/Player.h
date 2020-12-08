#ifndef WOLFENSTEIN3D_PLAYER_H_
#define WOLFENSTEIN3D_PLAYER_H_

#include <cstdint>
#include <vector>
#include "Exceptions/GameException.h"

class Player {
 private:
    uint8_t health;
    uint8_t ammo;
    std::vector<bool> weapons;
    int score;
    uint8_t lives;
    bool hasKey;
    bool isAlive;

    //Position
    float posX, posY;

    //Direction Variables
    float dirX, dirY;
    float camPlaneX, camPlaneY;

    //Movement Speed
    float moveSpeed, rotSpeed;

    //State Variable
    uint8_t state;

 public:
    /* Constructor */
    Player(float moveSpeed, float rotSpeed, float posX, float posY);

    void updatePlayer();

    void setState(uint8_t newState);

    void die();

    bool isDead();

    void shoot();

    void getHealth();

    void receiveShot(int damage);

    /* Escribe los primeros 16 bytes del buffer con la informacion de
     * la posicion del jugador de la siguiente manera (floats):
     * [ posX, posY, dirX, dirY ] */
    void getPositionData(uint8_t* msg);

    /* Escribe los primeros 24 bytes del buffer con la informacion de
     * la posicion del jugador de la siguiente manera (floats):
     * [ posX, posY, dirX, dirY, camPlaneX, camPlaneY ] */
    void getPositionDataWithPlane(uint8_t* msg);

    /* Destructor */
    ~Player();

private:
    void _moveForwards();
    void _moveBackwards();
    void _turnLeft();
    void _turnRight();
};

#endif  // WOLFENSTEIN3D_PLAYER_H_
