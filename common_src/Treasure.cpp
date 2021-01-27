#include "Treasure.h"

Treasure::Treasure(float _x, float _y, TextureID _texture, int _value) :
				Item(_x, _y, _texture, _value) {}

void Treasure::equipTo(PlayerActions& action) {
	action.use(this);
}

int Treasure::operator+(int score) const {
	return (score + this->value);
}

Treasure::~Treasure() {}