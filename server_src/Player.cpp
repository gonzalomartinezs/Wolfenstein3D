#include "Player.h"
#include "../common_src/Exceptions/ErrorMap.h"
#include <algorithm>
#include <iostream> //Borrar
#include <cmath>
#include <cstring>

#define INITIAL_AMMO 8
#define MAX_HEALTH 100
#define COLLECTIBLE_WEAPONS_AMOUNT 3
#define INITIAL_SCORE 0
#define TOTAL_LIVES 3

#define WALKABLE 0

//Actions
#define ISNOTMOVING 0
#define ISMOVINGFORWARDS 1
#define ISMOVINGBACKWARDS 2
#define ISTURNINGLEFT 3
#define ISTURNINGRIGHT 4

Player::Player(float moveSpeed, float rotSpeed, float posX, float posY) {
    this->moveSpeed = moveSpeed;
    this->rotSpeed = rotSpeed;
    this->posX = posX;
    this->posY = posY;
    this->dirX = 1;  // Initial Direction
    this->dirY = 0;  // Initial Direction
    this->camPlaneX = 0;  // Perpendicular to direction
    this->camPlaneY = 1;  // Perpendicular to direction
    this->state = ISNOTMOVING;

    this->weapons.resize(COLLECTIBLE_WEAPONS_AMOUNT, false);
    this->health = MAX_HEALTH;
    this->ammo = INITIAL_AMMO;
    this->score = INITIAL_SCORE;
    this->lives = TOTAL_LIVES;
    this->hasKey = false;
    this->isAlive = true;
}

void Player::updatePlayer(const Map& map) {
    float old_x = this->posX, old_y = this->posY;

    if (this->state != ISNOTMOVING) {
        if (this->state == ISMOVINGFORWARDS) {
            this->_moveForwards();
        } else if (this->state == ISMOVINGBACKWARDS) {
            this->_moveBackwards();
        } else if (this->state == ISTURNINGLEFT) {
            this->_turnLeft();
        } else if (this->state == ISTURNINGRIGHT) {
            this->_turnRight();
        } else {
            throw GameException("Player has an invalid state!");
        }
    }
    try {
        if (map.get(int(this->posX), int(this->posY)) != WALKABLE) {
            this->posX = old_x;
            this->posY = old_y;
        }
    } catch(const ErrorMap& e) {
        std::cerr << e.what() << std::endl;
    }
    // Borrar
    std::cout << "posX: " << this->posX;
    std::cout << ", posY: " << this->posY;
    std::cout << ", dirX: " << this->dirX;
    std::cout << ", dirY: " << this->dirY << std::endl;
}

void Player::setState(uint8_t newState) {
    this->state = newState;
}

void Player::die() {
    std::fill(this->weapons.begin(), this->weapons.end(), false);
    this->lives--;
    this->ammo = INITIAL_AMMO;
    this->health = MAX_HEALTH;

    /* Reiniciar posicion */
}

bool Player::isDead() {
    return this->isAlive;
}

void Player::shoot() {
    this->ammo--;
    /* Logica del disparo */
}

void Player::receiveShot(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->die();
    }
}

void Player::_moveForwards() {
    this->posX += this->dirX * this->moveSpeed;
    this->posY += this->dirY * this->moveSpeed;
}

void Player::_moveBackwards() {
    this->posX -= this->dirX * this->moveSpeed;
    this->posY -= this->dirY * this->moveSpeed;
}

void Player::_turnLeft() {
    float oldDirX = this->dirX;
    this->dirX = (this->dirX * cos(this->rotSpeed) - this->dirY * sin(this->rotSpeed));
    this->dirY = (oldDirX * sin(this->rotSpeed) + this->dirY * cos(this->rotSpeed));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = this->camPlaneX * cos(this->rotSpeed) - this->camPlaneY * sin(this->rotSpeed);
    this->camPlaneY = oldPlaneX * sin(this->rotSpeed) + this->camPlaneY * cos(this->rotSpeed);
}

void Player::_turnRight() {
    float oldDirX = this->dirX;
    this->dirX = (this->dirX * cos(-this->rotSpeed) - this->dirY * sin(-this->rotSpeed));
    this->dirY = (oldDirX * sin(-this->rotSpeed) + this->dirY * cos(-this->rotSpeed));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = (this->camPlaneX * cos(-this->rotSpeed) - this->camPlaneY * sin(-this->rotSpeed));
    this->camPlaneY = (oldPlaneX * sin(-this->rotSpeed) + this->camPlaneY * cos(-this->rotSpeed));
}

void Player::getPositionData(uint8_t *msg) {
    memcpy(msg, &this->posX, sizeof(float));
    memcpy(msg + sizeof(float), &this->posY, sizeof(float));
    memcpy(msg + 2 * sizeof(float), &this->dirX, sizeof(float));
    memcpy(msg + 3 * sizeof(float), &this->dirY, sizeof(float));
}

void Player::getPositionDataWithPlane(uint8_t *msg) {
    this->getPositionData(msg);
    memcpy(msg + 4 * sizeof(float), &this->camPlaneX, sizeof(float));
    memcpy(msg + 5 * sizeof(float), &this->camPlaneY, sizeof(float));
}

Player::~Player() {}
