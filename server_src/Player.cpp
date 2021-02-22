#include "Player.h"
#include "../common_src/Exceptions/ErrorMap.h"
#include "../common_src/Collider.h"
#include <algorithm>
#include <iostream> //Borrar
#include <cmath>
#include <cstring>
#include <string>

#define WALKABLE 0
#define WALL 1
#define DOOR 2
#define PI 3.14159
#define WALL_SIZE 1

//Actions
#define ISNOTMOVING 0
#define ISMOVINGFORWARDS 1
#define ISMOVINGBACKWARDS 2
#define ISTURNINGLEFT 3
#define ISTURNINGRIGHT 4
#define STARTSHOOTING 5
#define STOPSHOOTING 6
#define NEXT_WEAPON 7
#define PREV_WEAPON 8
#define INTERACT_WITH_DOOR 9

//Keys
#define KEY_POS_X "pos_x"
#define KEY_POS_Y "pos_y"
#define KEY_DIR_X "dir_x"
#define KEY_DIR_Y "dir_y"
#define KEY_MOVE_SPEED "move_speed"
#define KEY_ROT_SPEED "rot_speed"
#define KEY_SIZE "size"

Player::Player(const Configuration& config_stats,
            const Configuration& config_map,
            const uint8_t _player_number,
            std::string playerName,
            std::vector<Sound>& sounds) :
            DirectedPositionable(config_map.getFloat(KEY_POS_X),
            config_map.getFloat(KEY_POS_Y), config_map.getFloat(KEY_DIR_X),
            config_map.getFloat(KEY_DIR_Y), None), action(config_stats),
            sounds(sounds) {
    this->moveSpeed = config_stats.getFloat(KEY_MOVE_SPEED);
    this->rotSpeed = config_stats.getFloat(KEY_ROT_SPEED);
    this->initial_dir_x = this->dir_x;
    this->initial_dir_y = this->dir_y;
    this->initialPosX = this->x;
    this->initialPosY = this->y;
    this->camPlaneX = this->dir_y; // Rotation matrix 90 degrees clockwise
    this->camPlaneY = -this->dir_x; // Rotation matrix 90 degrees clockwise
    this->state = ISNOTMOVING;
    this->player_number = _player_number;
    this->player_size = config_stats.getFloat(KEY_SIZE);

    if (playerName.size() > 0) {
        this->name = playerName;
    } else {
        this->name = "Player_" + std::to_string(_player_number);
    }
}

void Player::lookForWallCollision(const Map& map, const Collider& collider) {
    for (int i = this->x-1; i <= this->x+1; ++i) {
        for (int j = this->y-1; j <= this->y+1; ++j) {
            if (map.get(i, j) > WALKABLE) {
                if (collider.collidesWith(i, j, WALL_SIZE, WALL_SIZE)) {
                    throw ErrorMap("Collision detected.");
                }
            }
        }
    }
}

void Player::lookForItem(Items& items, const Collider& collider) {
	for (size_t i = 0; i < items.size(); ++i) {
		if (items[i]->collidesWith(collider)) {
            try {
                items[i]->equipTo(this->action);
//                Player::makeSound(PickItemSFX);
                items.remove(i);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
	}
}

void Player::lookForDoor(Doors& doors, const Collider& collider) {
    for (size_t i = 0; i < doors.size(); ++i) {
        if (doors[i].collidesWith(collider)) {
            try {
                this->action.interactWith(doors[i]);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
            break;
        }
    }
}

void Player::updatePlayer(const Map& map, Items& items,
                        std::vector<Player*>& players, Doors& doors, double timeSlice) {

    if (!this->hasLost()) {
        float old_x = this->x, old_y = this->y;

        try {
            Player::_move(timeSlice);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        Collider collider = Player::getCollider();

        try {
            Player::lookForWallCollision(map, collider);
            Player::lookForItem(items, collider);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            this->x = old_x;
            this->y = old_y;
        }

        if (this->state == INTERACT_WITH_DOOR) {
            Player::lookForDoor(doors, collider);
        }

        if (this->action.isShooting()) {
            this->action.fireTheGun(players, this->player_number, map);
        }

        if (this->action.isDead()) {
            Player::_respawn(items);
        }

    } else {
        _sendPlayerToMordor();
    }
}

void Player::setState(uint8_t newState) {
    if (!this->hasLost()) {
        if (newState == STARTSHOOTING) {
            this->action.startShooting();
        } else if (newState == STOPSHOOTING) {
            this->action.stopShooting();
        } else if (newState == NEXT_WEAPON) {
            this->action.stopShooting();
            this->action.nextWeapon();
        } else if (newState == PREV_WEAPON) {
            this->action.stopShooting();
            this->action.prevWeapon();
        } else {
            this->state = newState;
        }
    }
}

void Player::makeSound(SoundID sound) {
    this->sounds.emplace_back(this->x, this->y, sound);
}

bool Player::hasLost() {
    return this->action.playerHasLost();
}

bool Player::isDead() {
    return this->action.isDead();
}

Collider Player::getCollider() const {
    return Collider(this->x, this->y, this->player_size);
}

void Player::receiveShot(uint8_t damage) {
    this->action.receiveShot(damage);
}

void Player::increaseBulletCounter(uint8_t bulletsAmount) {
    this->action.increaseBulletCounter(bulletsAmount);
}

void Player::increaseKillCounter() {
    this->action.increaseKillCounter();
}

void Player::useBullets(uint8_t bulletsAmount) {
    this->action.useBullets(bulletsAmount);
}

bool Player::hasBullets(uint8_t bulletsAmount) {
    return this->action.hasBullets(bulletsAmount);
}

std::string Player::getName() {
    return this->name;
}

int Player::getKills() {
    return this->action.getKills();
}

int Player::getScore() {
    return this->action.getScore();
}

int Player::getBulletsFired() {
    return this->action.getBulletsFired();
}

uint8_t Player::getWeaponID() const {
    return this->action.getWeaponID();
}

void Player::_moveForwards(double timeSlice) {
    this->x += this->dir_x * this->moveSpeed * static_cast<float>(timeSlice);
    this->y += this->dir_y * this->moveSpeed * static_cast<float>(timeSlice);
}

void Player::_moveBackwards(double timeSlice) {
    this->x -= this->dir_x * this->moveSpeed * static_cast<float>(timeSlice);
    this->y -= this->dir_y * this->moveSpeed * static_cast<float>(timeSlice);
}

void Player::_turnLeft(double timeSlice) {
    float step = this->rotSpeed * static_cast<float>(timeSlice);
    float oldDirX = this->dir_x;
    this->dir_x = (this->dir_x * cos(step) - this->dir_y * sin(step));
    this->dir_y = (oldDirX * sin(step) + this->dir_y * cos(step));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = this->camPlaneX * cos(step) - this->camPlaneY * sin(step);
    this->camPlaneY = oldPlaneX * sin(step) + this->camPlaneY * cos(step);
}

void Player::_turnRight(double timeSlice) {
    float step = this->rotSpeed * static_cast<float>(timeSlice);
    float oldDirX = this->dir_x;
    this->dir_x = (this->dir_x * cos(-step) - this->dir_y * sin(-step));
    this->dir_y = (oldDirX * sin(-step) + this->dir_y * cos(-step));

    float oldPlaneX = this->camPlaneX;
    this->camPlaneX = (this->camPlaneX * cos(-step) -  this->camPlaneY * sin(-step));
    this->camPlaneY = (oldPlaneX * sin(-step) + this->camPlaneY * cos(-step));
}

void Player::_move(double timeSlice) {
    if (this->state != ISNOTMOVING) {
        if (this->state == ISMOVINGFORWARDS) {
            this->_moveForwards(timeSlice);
        } else if (this->state == ISMOVINGBACKWARDS) {
            this->_moveBackwards(timeSlice);
        } else if (this->state == ISTURNINGLEFT) {
            this->_turnLeft(timeSlice);
        } else if (this->state == ISTURNINGRIGHT) {
            this->_turnRight(timeSlice);
        } else {
            throw GameException("Player has an invalid state!");
        }
    }
}

void Player::_respawn(Items& items) {
    this->action.die(&items, this->x, this->y);

    this->dir_x = this->initial_dir_x;
    this->dir_y = this->initial_dir_y;

    this->camPlaneX = this->dir_y;
    this->camPlaneY = -this->dir_x;

    this->x = this->initialPosX;
    this->y = this->initialPosY;
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

void Player::getHUDData(uint8_t *msg) {
    this->action.getHUDInfo(msg);
}

void Player::_sendPlayerToMordor() {
    /* Posicion invalida, nunca un jugador podria ver o estar en esa posicion  */
    this->x = 0.5;
    this->y = 0.5;
}

Player::~Player() {}
