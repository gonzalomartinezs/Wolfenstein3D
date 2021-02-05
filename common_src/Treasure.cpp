#include "Treasure.h"

Treasure::Treasure(const Configuration& config, float _x, float _y) :
					Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)) {}

void Treasure::equipTo(PlayerActions& action) {
	action.use(this);
}

int Treasure::operator+(int score) const {
	return (score + this->value);
}

Treasure::~Treasure() {}