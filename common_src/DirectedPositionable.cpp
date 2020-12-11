#include "DirectedPositionable.h"
#include <cmath>

DirectedPositionable::DirectedPositionable(float pos_x, float pos_y,
                                           float dir_x, float dir_y,
                                           TextureID texture):
                                           Positionable(pos_x, pos_y, texture){
    float norm = std::sqrt(dir_x*dir_x + dir_y*dir_y);
    this-> dir_x = dir_x/norm;
    this-> dir_y = dir_y/norm;
}

DirectedPositionable& DirectedPositionable::operator=(const DirectedPositionable &other) {
    this->x = other.x;
    this->y = other.y;
    this->dir_x = other.dir_x;
    this->dir_y = other.dir_y;
    return *this;
}

void DirectedPositionable::setDirX(float new_dir) {
    this->dir_x = new_dir;
}

void DirectedPositionable::setDirY(float new_dir) {
    this->dir_y = new_dir;
}

float DirectedPositionable::getDirX() const {
    return this->dir_x;
}

float DirectedPositionable::getDirY() const {
    return this->dir_y;
}

void DirectedPositionable::setTexture(TextureID texture) {
    this->texture = texture;
}