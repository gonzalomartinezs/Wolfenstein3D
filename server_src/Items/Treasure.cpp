#include "Treasure.h"

Treasure::Treasure(const Configuration& config, float _x, float _y,
				TextureID _texture) :
				Item(_x, _y, _texture, config.getInt(KEY_VALUE),
					config.getFloat(KEY_RADIUS)) {}

void Treasure::equipTo(PlayerActions& action) {
	action.use(this);
}

Treasure::~Treasure() {}
