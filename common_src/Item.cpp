#include "Item.h"

Item::Item(float _x, float _y, TextureID _texture, int _value, float radius) :
			Positionable(_x, _y, _texture), value(_value),
			collider(_x, _y, radius) {}

bool Item::collidesWith(const Collider& other) const {
	return this->collider.collidesWith(other);
}

Item::~Item() {}