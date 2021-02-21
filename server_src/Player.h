#ifndef WOLFENSTEIN3D_PLAYER_H_
#define WOLFENSTEIN3D_PLAYER_H_

#include <cstdint>
#include <vector>
#include <string>

#include "Sound.h"
#include "Exceptions/GameException.h"
#include "PlayerActions.h"
#include "../common_src/Map.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Items.h"
#include "../common_src/Item.h"
#include "../common_src/Configuration.h"
#include "../common_src/Doors.h"

#define POS_DATA_PLANE_SIZE 24
#define POS_DATA_SIZE 16

class Player : public DirectedPositionable {
protected:
    PlayerActions action;
    std::vector<Sound>& sounds;
    float camPlaneX, camPlaneY;
    float initial_dir_x, initial_dir_y;
    float initialPosX, initialPosY;
    uint8_t player_number;
    std::string name;

    //Movement Speed
    float moveSpeed, rotSpeed;

    //State Variable
    uint8_t state;

    float player_size;

public:
    /* Constructor */
    Player(const Configuration& config_stats,
           const Configuration& config_map,
           const uint8_t _player_number,
           std::string name,
           std::vector<Sound>& sounds);

    // Actualiza el estado del jugador
    void updatePlayer(const Map& map, Items& items,
                        std::vector<Player*>& players, Doors& doors, double timeSlice);

    // Asigna el siguiente estado del jugador
    void setState(uint8_t newState);

    // Obtiene el estado actual
    virtual void getState(std::vector<Player*> &players,
                        int botNumber, const Map &map) {}

    void makeSound(SoundID sound);

    // Devuelve true en caso de estar muerto, false en caso contrario
    bool isDead();

    // Reduce `damage` la vida del jugador
    void receiveShot(uint8_t damage);
    // Incrementa el contador de balas
    void increaseBulletCounter(uint8_t bulletsAmount);
    // Incrementa el contador de jugadores matados
    void increaseKillCounter();
    // Reduce `bulletsAmount` a las balas
    void useBullets(uint8_t bulletsAmount);
    // Devuelve tru en caso de tener bulletsAmount o más,
    // false en caso contrario
    bool hasBullets(uint8_t bulletsAmount);

    // Obtiene el nombre del jugador
    std::string getName();
    // Obtiene la cantidad de jugadores matados
    int getKills();
    // Obtiene la puntuación del jugador
    int getScore();
    // Obtiene la cantidad de balas disparadas
    int getBulletsFired();

    // Obtiene el id del arma
    uint8_t getWeaponID() const;

    // Obtiene el collisionador del jugador
    Collider getCollider() const;

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
    virtual ~Player();

private:
    void lookForItem(Items& items, const Collider& collider);
    void lookForWallCollision(const Map& map, const Collider& collider);
    void lookForDoor(Doors& doors, const Collider& collider);
    void _move(double timeSlice);
    void _respawn(Items& items);
    void _moveForwards(double timeSlice);
    void _moveBackwards(double timeSlice);
    void _turnLeft(double timeSlice);
    void _turnRight(double timeSlice);
};

#endif  // WOLFENSTEIN3D_PLAYER_H_
