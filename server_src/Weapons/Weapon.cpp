#include "Weapon.h"
#include <cstring>

#define PI 3.1415926
#define POSITION_DATA_SIZE 16
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

bool Weapon::_isShootable(uint8_t* thisPlayerInfo, uint8_t* otherPlayerInfo, const Map& map) {
    bool isShootable = false;
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



    return isShootable;
}

float getAngleToPlayer() {
    return PI;
}

void Weapon::shoot(std::vector<Player>& players, int shootingPlayerNumber, const Map& map) {
    bool shotHit = false;
    float hitProbability;
    uint8_t thisPlayerInfo[POSITION_DATA_SIZE], otherPlayerInfo[POSITION_DATA_SIZE];
    players[shootingPlayerNumber].getPositionData(thisPlayerInfo);

    for (size_t i = 0; i < players.size(); i++) {
        if (static_cast<int>(i) != shootingPlayerNumber) {
            players[i].getPositionData(otherPlayerInfo);
            if (_isShootable(thisPlayerInfo, otherPlayerInfo, map)) {

                shotHit = false;//Aca poner algo
                if (shotHit) {
                    break;
                }
            }
        }

    }
}

Weapon::~Weapon() {}
