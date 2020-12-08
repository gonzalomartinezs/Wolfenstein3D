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

Player::Player(float moveSpeed, float rotSpeed, float posX, float posY) :
                DirectedPositionable(posX, posY, 1, 0) {
    this->moveSpeed = moveSpeed;
    this->rotSpeed = rotSpeed;
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
    float old_x = this->x, old_y = this->y;

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
        if (map.get(int(this->x), int(this->y)) != WALKABLE) {
            this->x = old_x;
            this->y = old_y;
        }
    } catch(const ErrorMap& e) {
        std::cerr << e.what() << std::endl;
    }
    // Borrar
    std::cout << "posX: " << this->x;
    std::cout << ", posY: " << this->y;
    std::cout << ", dir_x: " << this->dir_x;
    std::cout << ", dir_y: " << this->dir_y << std::endl;
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
    this->x += this->dir_x * this->moveSpeed;
    this->y += this->dir_y * this->moveSpeed;
}

void Player::_moveBackwards() {
    this->x -= this->dir_x * this->moveSpeed;
    this->y -= this->dir_y * this->moveSpeed;
}

void Player::_turnLeft() {
    float oldDirX = this->dir_x;
    this->dir_x = (this->dir_x * cos(this->rotSpeed) - this->dir_y * sin(this->rotSpeed));
    this->dir_y = (oldDirX * sin(this->rotSpeed) + this->dir_y * cos(this->rotSpeed));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = this->camPlaneX * cos(this->rotSpeed) - this->camPlaneY * sin(this->rotSpeed);
    this->camPlaneY = oldPlaneX * sin(this->rotSpeed) + this->camPlaneY * cos(this->rotSpeed);
}

void Player::_turnRight() {
    float oldDirX = this->dir_x;
    this->dir_x = (this->dir_x * cos(-this->rotSpeed) - this->dir_y * sin(-this->rotSpeed));
    this->dir_y = (oldDirX * sin(-this->rotSpeed) + this->dir_y * cos(-this->rotSpeed));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = (this->camPlaneX * cos(-this->rotSpeed) - this->camPlaneY * sin(-this->rotSpeed));
    this->camPlaneY = (oldPlaneX * sin(-this->rotSpeed) + this->camPlaneY * cos(-this->rotSpeed));
}

void Player::getPositionData(uint8_t *msg) {
    memcpy(msg, &this->x, sizeof(float));
    memcpy(msg + sizeof(float), &this->y, sizeof(float));
    memcpy(msg + 2 * sizeof(float), &this->dir_x, sizeof(float));
    memcpy(msg + 3 * sizeof(float), &this->dir_y, sizeof(float));
}

void Player::getPositionDataWithPlane(uint8_t *msg) {
    this->getPositionData(msg);
    memcpy(msg + 4 * sizeof(float), &this->camPlaneX, sizeof(float));
    memcpy(msg + 5 * sizeof(float), &this->camPlaneY, sizeof(float));
}

Player::~Player() {}
