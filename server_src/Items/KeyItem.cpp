#include "KeyItem.h"
#include "../../common_src/Exceptions/ItemException.h"
#include "../Key.h"

#define VALUE 0

KeyItem::KeyItem(const Configuration& config, float _x, float _y) : 
			Item(_x, _y, KeyItem_, VALUE, config.getFloat(KEY_RADIUS)) {}

KeyItem::KeyItem(float _x, float _y, int _radius) :
				Item(_x, _y, KeyItem_, VALUE, _radius) {}

void KeyItem::equipTo(PlayerActions& action) {
	action.equipKey();
}

KeyItem::~KeyItem() {}
