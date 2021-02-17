#include "KeyItem.h"

#define VALUE 0

KeyItem::KeyItem(const Configuration& config, float _x, float _y) : 
				Item(_x, _y,
					static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
					VALUE,
					config.getFloat(KEY_RADIUS)) {}

void KeyItem::equipTo(PlayerActions& action) {
	action.equip(this->value);
}

KeyItem::~KeyItem() {}
