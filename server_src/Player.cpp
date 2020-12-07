#include "Player.h"
#include <algorithm>
#include <iostream> //Borrar
#include <cmath>

#define INITIAL_AMMO 8
#define MAX_HEALTH 100
#define COLLECTIBLE_WEAPONS_AMOUNT 3
#define INITIAL_SCORE 0
#define TOTAL_LIVES 3

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
    this->state = ISNOTMOVING;

    this->weapons.resize(COLLECTIBLE_WEAPONS_AMOUNT, false);
    this->health = MAX_HEALTH;
    this->ammo = INITIAL_AMMO;
    this->score = INITIAL_SCORE;
    this->lives = TOTAL_LIVES;
    this->hasKey = false;
    this->isAlive = true;
}

void Player::updatePlayer() {
    if (this->state != ISNOTMOVING) {
        if (this->state == ISMOVINGFORWARDS) {
            this->_moveForwards();
        }
        if (this->state == ISMOVINGBACKWARDS) {
            this->_moveBackwards();
        }
        if (this->state == ISTURNINGLEFT) {
            this->_turnLeft();
        }
        if (this->state == ISTURNINGRIGHT) {
            this->_turnRight();
        }
    }
    //Throw si no es ninguna
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
}

void Player::_turnRight() {
    float oldDirX = this->dirX;
    this->dirX = (this->dirX * cos(-this->rotSpeed) - this->dirY * sin(-this->rotSpeed));
    this->dirY = (oldDirX * sin(-this->rotSpeed) + this->dirY * cos(-this->rotSpeed));
}

Player::~Player() {}
