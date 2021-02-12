#include "KeyItem.h"

KeyItem::KeyItem(const Configuration& config, float _x, float _y) : 
				Item(_x, _y,
					static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
					config.getInt(KEY_VALUE),
					config.getFloat(KEY_RADIUS)) {}

void KeyItem::equipTo(PlayerActions& action) {
	action.equip(this->value);
}

KeyItem::~KeyItem() {}