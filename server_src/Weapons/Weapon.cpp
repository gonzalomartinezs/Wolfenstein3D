#include "Weapon.h"
#include <cstring>
#include <iostream> //borrar

#define PI 3.1415926
#define POSITION_DATA_SIZE 16
#define WALKABLE 0

#define FLOAT_SIZE sizeof(float)

const float MAX_SHOOTING_ANGLE = PI/6;
const float MAX_SHOOTING_DISTANCE = 10;

Weapon::Weapon() {
    this->isShooting = false;
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

    angle = acos((dirXP1 * xP2 + dirYP1 * yP2) / std::sqrt(xP2 * xP2 + yP2 * yP2));
    distance = std::sqrt(((xP1 - xP2) * (xP1 - xP2)) + ((yP1 - yP2) * (yP1 - yP2)));
    probability = _angleProbabilityFunction(angle) * _distanceProbabilityFunction(distance);

    return (probability >= _randomNumberGenerator());
 }

bool Weapon::_isShootable(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map) {
    bool isShootable = true;
    float xP1, xP2, yP1, yP2;
    float dirX, dirY, stepX, stepY, norm;
    memcpy(&xP1, thisPlayerInfo, FLOAT_SIZE);
    memcpy(&yP1, thisPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);
    memcpy(&xP2, otherPlayerInfo, FLOAT_SIZE);
    memcpy(&yP2, otherPlayerInfo + FLOAT_SIZE, FLOAT_SIZE);

    dirX = xP2 - xP1;
    dirY = yP2 - yP1;
    norm = std::sqrt(dirX * dirX + dirY * dirY);

    stepX = dirX/(norm * 10);  // Step
    stepY = dirY/(norm * 10);  // Step

    for (int i = 0; i < static_cast<int>(10 * norm); i++) {
        std::cout << xP1 + i * stepX << ' ' << yP1 + i * stepY << std::endl;
        std::cout << "A ver esto: "<< map.get(2, 2) << std::endl;
        if (map.get(int(xP1 + i * stepX), int(yP1 + i * stepY) != WALKABLE)) {
            isShootable = false;
            break;
        }
    }
    return isShootable;
}

void Weapon::shoot(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) {
    bool shotHit = false;
    uint8_t thisPlayerInfo[POSITION_DATA_SIZE], otherPlayerInfo[POSITION_DATA_SIZE];
    players[shootingPlayerNumber].getPositionData(thisPlayerInfo);

    for (size_t i = 0; i < players.size(); i++) {
        if (static_cast<int>(i) != shootingPlayerNumber) {
            players[i].getPositionData(otherPlayerInfo);
            if (_isShootable(thisPlayerInfo, otherPlayerInfo, map)) {
                std::cout << "Is shootable" << std::endl;
                shotHit = _runProbability(thisPlayerInfo, otherPlayerInfo);
                if (shotHit) {
                    std::cout << "La bala le llego" << std::endl;
                    break;
                }
                else {
                    std::cout << "La bala no llego" << std::endl;
                }
            }
        }

    }
}

Weapon::~Weapon() {}
