#ifndef WOLFENSTEIN3D_PLAYER_H_
#define WOLFENSTEIN3D_PLAYER_H_

#include <cstdint>
#include <vector>

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
    //Movement Speed
    float moveSpeed, rotSpeed;

public:
    /* Constructor */
    Player(float moveSpeed, float rotSpeed, float posX, float posY);

    void die();

    bool isDead();
    void shoot();

    void move(int keyType);

    void getHealth();
    void receiveShot(int damage);

    /* Destructor */
    ~Player();

private:
    void _moveUp();
    void _moveDown();
    void _turnLeft();
    void _turnRight();

};

#endif  // WOLFENSTEIN3D_PLAYER_H_
