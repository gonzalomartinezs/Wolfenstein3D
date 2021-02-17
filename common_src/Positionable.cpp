#include "Positionable.h"
#include <math.h>

Positionable &Positionable::operator=(const Positionable &other) {
    this->x = other.x;
    this->y = other.y;
    this->texture = other.texture;
    return *this;
}

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


float Positionable::distanceTo(Positionable &other) const{
    return sqrt(pow(this->x-other.getX(), 2) +
                        pow(this->y-other.getY(), 2));
}


TextureID Positionable::getTexture() {
    return this->texture;
}
