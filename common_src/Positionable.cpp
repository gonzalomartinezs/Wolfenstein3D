#include "Positionable.h"

void Positionable::setX(float new_x) {
    this->x = new_x;
}

void Positionable::setY(float new_y) {
    this->y = new_y;
}

void Positionable::moveX(float x_movement) {
    this->x += x_movement;
}

void Positionable::moveY(float y_movement) {
    this->y += y_movement;
}

float Positionable::getX() const{
    return this->x;
}

float Positionable::getY() const{
    return this->y;
}
