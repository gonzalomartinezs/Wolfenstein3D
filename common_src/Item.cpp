#include "Item.h"

Item::Item(float _x, float _y, TextureID& _texture, int _value) :
			Positionable(_x, _y, _texture), value(_value) {}
/*
bool Item::collidesWith(const Collider& other) {
	//Logica del collider
	return false;
}
*/
Item::~Item() {}