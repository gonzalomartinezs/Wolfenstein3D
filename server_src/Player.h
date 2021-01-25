#ifndef WOLFENSTEIN3D_PLAYER_H_
#define WOLFENSTEIN3D_PLAYER_H_

#include <cstdint>
#include <vector>
#include "Exceptions/GameException.h"
#include "PlayerActions.h"
#include "../common_src/Map.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Items.h"
#include "../common_src/Item.h"
#include "../common_src/Configuration.h"

class Player : public DirectedPositionable {
private:
    PlayerActions action;
    float camPlaneX, camPlaneY;
    int playerNumber;
    Weapon* weapon;

    //Movement Speed
    float moveSpeed, rotSpeed;

    //State Variable
    uint8_t state;

public:
    /* Constructor */
//    Player(float moveSpeed, float rotSpeed, float posX, float posY);
    Player(const Configuration& config, const std::string& player_number, const int playerNumber);

    void updatePlayer(const Map& map, Items& items, std::vector<Player>& players);

    void setState(uint8_t newState);

    void die();

    bool isDead();

    void shoot();

    void getHealth();

    void receiveShot(uint8_t damage);

    /* Escribe los primeros 16 bytes del buffer con la informacion de
     * la posicion del jugador de la siguiente manera (floats):
     * [ posX, posY, dirX, dirY ] */
    void getPositionData(uint8_t* msg);

    /* Escribe los primeros 24 bytes del buffer con la informacion de
     * la posicion del jugador de la siguiente manera (floats):
     * [ posX, posY, dirX, dirY, camPlaneX, camPlaneY ] */
    void getPositionDataWithPlane(uint8_t* msg);

    void getHUDData(uint8_t* msg);

    /* Destructor */
    ~Player();

private:
    void look_for_item(Items& items);
    void look_for_collision(const Map& map);
    void _moveForwards();
    void _moveBackwards();
    void _turnLeft();
    void _turnRight();
};

#endif  // WOLFENSTEIN3D_PLAYER_H_
