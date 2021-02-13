#include "Weapon.h"
#include <cstring>
#include "../Exceptions/GameException.h"
#include <iostream> //borrar

#define PI 3.1415926
#define POSITION_DATA_SIZE 16
#define DIVISIONS_AMOUNT 10
#define WALKABLE 0
#define FLOAT_SIZE sizeof(float)
#define BULLETS_PER_SHOT 1

const float MAX_SHOOTING_ANGLE = PI/6.f;
const float MAX_SHOOTING_DISTANCE = 10;

Weapon::Weapon(int _id) : id(_id), texture(None), item_radius(0) {
    this->weaponIsShooting = false;
}

Weapon::Weapon(int _id, TextureID _texture, float radius) : id(_id),
                texture(_texture), item_radius(radius) {
    this->weaponIsShooting = false;   
}

Item* Weapon::getWeaponItem(float x, float y) {
    throw GameException("Can't get this weapon as item.");
}

float Weapon::_randomNumberGenerator() {
    return (static_cast<float>(this->rd())/static_cast<float>(this->rd.max()));
}

float Weapon::_angleProbabilityFunction(float angle) {
    float probability = (-1/MAX_SHOOTING_ANGLE * std::abs(angle)) + 1;
    if (probability < 0 ) {
        probability = 0;
    }
    return probability;
}

float Weapon::_distanceProbabilityFunction(float distance) {
    float probability = (-1/MAX_SHOOTING_DISTANCE * distance) + 1;
    if (probability < 0) {
        probability = 0;
    }
    return probability;
}

bool Weapon::_runProbability(uint8_t *thisPlayerInfo, uint8_t *otherPlayerInfo) {
    float dirXP1, xP2, dirYP1, yP2, xP1, yP1;
    float angle, distance, probability;
    memcpy(&dirXP1, thisPlayerInfo + 2 * FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&dirYP1, thisPlayerInfo + 3 * FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&xP2, otherPlayerInfo, FLOAT_SIZE);
    memcpy(&yP2, otherPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&xP1, thisPlayerInfo, FLOAT_SIZE);
    memcpy(&yP1, thisPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);

    float diffX = xP2 - xP1;
    float diffY = yP2 - yP1;

    angle = acos((dirXP1 * diffX + dirYP1 * diffY) / std::sqrt(diffX * diffX + diffY * diffY));
    distance = std::sqrt((diffX * diffX) + (diffY * diffY));
    probability = _angleProbabilityFunction(angle) * _distanceProbabilityFunction(distance);

    return (probability >= _randomNumberGenerator());
 }

bool Weapon::_isInTheFieldOfView(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map) {
    bool isInTheFieldOfView = true;
    float xP1, xP2, yP1, yP2;
    float dirX, dirY, stepX, stepY, norm;
    memcpy(&xP1, thisPlayerInfo, FLOAT_SIZE);
    memcpy(&yP1, thisPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&xP2, otherPlayerInfo, FLOAT_SIZE);
    memcpy(&yP2, otherPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);

    dirX = xP2 - xP1;
    dirY = yP2 - yP1;
    norm = std::sqrt(dirX * dirX + dirY * dirY);

    stepX = dirX/(norm * DIVISIONS_AMOUNT);  // Step de norma igual a 1/10
    stepY = dirY/(norm * DIVISIONS_AMOUNT);  // Step de norma igual a 1/10

    for (int i = 0; i < static_cast<int>(DIVISIONS_AMOUNT * norm); i++) {
        if (map.get(int(xP1 + i * stepX), int(yP1 + i * stepY)) != WALKABLE) {
            isInTheFieldOfView = false;
            break;
        }
    }
    return isInTheFieldOfView;
}

void Weapon::shoot(std::vector<Player*>& players, int shootingPlayerNumber, const Map& map) {
    bool shotHit = false;
    uint8_t thisPlayerInfo[POSITION_DATA_SIZE], otherPlayerInfo[POSITION_DATA_SIZE];
    players[shootingPlayerNumber]->getPositionData(thisPlayerInfo);

    if (players[shootingPlayerNumber]->hasBullets()) {
        players[shootingPlayerNumber]->increaseBulletCounter(BULLETS_PER_SHOT);
        players[shootingPlayerNumber]->useBullets(BULLETS_PER_SHOT);

        for (size_t i = 0; i < players.size(); i++) {
            if (static_cast<int>(i) != shootingPlayerNumber) {
                players[i]->getPositionData(otherPlayerInfo);
                if (_isInTheFieldOfView(thisPlayerInfo, otherPlayerInfo, map)) {
                    shotHit = _runProbability(thisPlayerInfo, otherPlayerInfo);
                    if (shotHit) {
                        /* Bajar vida del jugador con el que impacto */
                        players[i]->receiveShot(static_cast<uint8_t>
                        (this->_randomNumberGenerator() * 10) + 1);  // Rango [1, 10]
                        if (players[i]->isDead()) {
                            players[shootingPlayerNumber]->increaseKillCounter();
                        }
                        break;
                    }
                }
            }
        }
    }
}

bool Weapon::isShooting() {
    return this->weaponIsShooting;
}

void Weapon::stopShooting() {
    this->weaponIsShooting = false;
}

bool Weapon::operator==(int other_id) const {
    return (this->id == other_id);
}

Weapon::~Weapon() {}
