#include "Knife.h"
#include <cstring>

#define POSITION_DATA_SIZE 16
#define FLOAT_SIZE sizeof(float)
#define KNIFE_RANGE 0.5

Knife::Knife() : Weapon(KNIFE) {}

void Knife::startShooting() {
    this->weaponIsShooting = true;
}

void Knife::fireTheGun(std::vector<Player> &players, int shootingPlayerNumber, const Map &map) {
    uint8_t thisPlayerInfo[POSITION_DATA_SIZE], otherPlayerInfo[POSITION_DATA_SIZE];
    players[shootingPlayerNumber].getPositionData(thisPlayerInfo);

    for (size_t i = 0; i < players.size(); i++) {
        if (static_cast<int>(i) != shootingPlayerNumber) {
            players[i].getPositionData(otherPlayerInfo);
            if (_isInTheKnifeRange(thisPlayerInfo, otherPlayerInfo)) {
                players[i].receiveShot(5); // Cambiar
                break;
            }
        }
    }
    this->weaponIsShooting = false;
}

bool Knife::_isInTheKnifeRange(uint8_t *thisPlayerInfo, uint8_t *otherPlayerInfo) {
    float xP1, xP2, yP1, yP2;
    float dirX, dirY, distance;
    memcpy(&xP1, thisPlayerInfo, FLOAT_SIZE);
    memcpy(&yP1, thisPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&xP2, otherPlayerInfo, FLOAT_SIZE);
    memcpy(&yP2, otherPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);

    dirX = xP2 - xP1;
    dirY = yP2 - yP1;

    distance = std::sqrt(dirX * dirX + dirY * dirY);

    return (distance <= KNIFE_RANGE);
}

Knife::~Knife() {}