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

public:
    /* Constructor */
    Player();

    void die();

    void shoot();

    void getHealth();
    void receiveShot();

    /* Destructor */
    ~Player();
};

#endif  // WOLFENSTEIN3D_PLAYER_H_
