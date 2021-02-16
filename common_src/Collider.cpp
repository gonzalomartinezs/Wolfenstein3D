#include "Collider.h"
#include <cmath>

Collider::Collider(float _x, float _y, float _radius) : x(_x), y(_y),
 					radius(_radius) {}

bool Collider::collidesWith(float _x, float _y, float width, 
							float height) const {
	float aux_x = this->x, aux_y = this->y;

	if (this->x <= _x) aux_x = _x;
	else if (this->x > _x + width) aux_x = _x + width;

	if (this->y <= _y) aux_y = _y;
	else if (this->y > _y + height) aux_y = _y + height;

	float distance = sqrt(pow(this->x - aux_x, 2) + pow(this->y - aux_y, 2));

	return (distance <= this->radius);
}

bool Collider::collidesWith(const Collider& other) const {
	float distance = sqrt(pow(this->x - other.x, 2) +
						pow(this->y - other.y, 2));

	return (distance <= this->radius + other.radius);
}

float Collider::getRadius() const {
	return this->radius;
}

Collider::~Collider() {}
