#include "KeyItem.h"
#include "Exceptions/ItemException.h"
#include "../server_src/Key.h"

#define VALUE 0

KeyItem::KeyItem(const Configuration& config, float _x, float _y) : 
			Item(_x, _y, KeyItem_, VALUE, config.getFloat(KEY_RADIUS)) {}

KeyItem::KeyItem(float _x, float _y, TextureID _texture, int _radius) :
				Item(_x, _y, _texture, VALUE, _radius) {}

void KeyItem::equipTo(PlayerActions& action) {
	action.equipKey();
}

KeyItem::~KeyItem() {}
