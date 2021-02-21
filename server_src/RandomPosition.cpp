#include "RandomPosition.h"

#define RANGE 10
#define FRACTION 10.0f

RandomPosition::RandomPosition(const float _x, const float _y) :
					x(_x), y(_y), range_x((int(_x) - _x)),
					range_y((int(_y) - _y)), direction(1) {}

float RandomPosition::getX() {
	float aux = RandomPosition::calculateAux();

	this->direction = this->direction * (-1);

	return (x + aux);
}

float RandomPosition::getY() {
	float aux = RandomPosition::calculateAux();

	this->direction = this->direction * (-1);

	return (y + aux);
}

float RandomPosition::calculateAux() {
	return ((this->rd() % RANGE) / FRACTION) * direction;
}

RandomPosition::~RandomPosition() {}
