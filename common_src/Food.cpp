#include "Food.h"

Food::Food(float _x, float _y, TextureID& _texture, int _value) :
			Item(_x, _y, _texture, _value) {}

void Food::equipTo(PlayerAttributes& attributes) {
	attributes.addHealth(this->value);
}

Food::~Food() {}