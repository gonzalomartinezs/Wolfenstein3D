#include "BulletItem.h"
#include "Exceptions/WeaponItemException.h"

#define KEY_MAX_BULLETS "max_bullets"

BulletItem::BulletItem(const Configuration& config, float _x, float _y)
				: Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)),
						MAX_BULLETS(config.getInt(KEY_MAX_BULLETS)) {}

void BulletItem::equipTo(PlayerActions& action) {
	action.use(this);
}

int BulletItem::operator+(int bullets) const {
	if (bullets >= this->MAX_BULLETS) 
		throw WeaponItemException("Can't take more bullets.");

	int new_bullets = this->value + bullets;

	if (new_bullets > this->MAX_BULLETS) new_bullets = this->MAX_BULLETS;

	return new_bullets;
}

BulletItem::~BulletItem() {}