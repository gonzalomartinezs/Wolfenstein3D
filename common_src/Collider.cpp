#include "Collider.h"
#include <cmath>

#define SQUARE_SIZE 1

Collider::Collider(float _x, float _y, float _radius) : x(_x), y(_y),
 					radius(_radius) {}

bool Collider::collidesWith(float _x, float _y) const {
	float aux_x = this->x, aux_y = this->y;

	if (this->x < _x) aux_x = _x;
	else if (this->x > _x + SQUARE_SIZE) aux_x = _x + SQUARE_SIZE;

	if (this->y < _y) aux_y = _y;
	else if (this->y > _y + SQUARE_SIZE) aux_y = _y + SQUARE_SIZE;

	float distance = sqrt(pow(this->x - aux_x, 2) + pow(this->y - aux_y, 2));

	return (distance <= this->radius);
}

bool Collider::collidesWith(const Collider& other) const {
	float distance = sqrt(pow(this->x - other.x, 2) +
						pow(this->y - other.y, 2));

	return (distance <= this->radius + other.radius);
}

Collider::~Collider() {}