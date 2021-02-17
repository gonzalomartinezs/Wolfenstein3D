#include "Key.h"
#include "Exceptions/GameException.h"
#include "../common_src/KeyItem.h"

#define KEY_TEXTURE "texture"
#define KEY_RADIUS "radius"

Key::Key(const Configuration& config) : 
		item_texture(static_cast<TextureID>(config.getInt(KEY_TEXTURE))),
		item_radius(config.getFloat(KEY_RADIUS)) , available(false) {}

void Key::equip() {
	if (this->available) throw GameException("Can't equip key,"
											" already has one.");

	this->available = true;
}

bool Key::has() const {
	return this->available;
}

Item* Key::getItem(float x, float y) const {
	return new KeyItem(x, y, this->item_texture, this->item_radius);
}

void Key::used() {
	this->available = false;
}

Key::~Key() {}
