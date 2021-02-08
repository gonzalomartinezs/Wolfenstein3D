#include "Item.h"

Item::Item(float _x, float _y, TextureID _texture, int _value, float radius) :
			Positionable(_x, _y, _texture), value(_value),
			collider(_x, _y, radius) {}

int Item::operator+(int other_value) const {
	return (other_value + this->value);
}

bool Item::collidesWith(const Collider& other) const {
	return this->collider.collidesWith(other);
}
/*
int Item::getID() const {
	return this->id;
}
*/
Item::~Item() {}