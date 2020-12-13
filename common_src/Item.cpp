#include "Item.h"

Item::Item(float _x, float _y, TextureID& _texture, int _value) :
			Positionable(_x, _y, _texture), value(_value) {}

Item::~Item() {}