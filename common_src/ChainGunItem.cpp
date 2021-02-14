#include "ChainGunItem.h"
#include "../server_src/Weapons/ChainGun.h"
#include "Exceptions/WeaponItemException.h"

#define KEY_SHOTS "time_between_shots"

ChainGunItem::ChainGunItem(const Configuration& config, float _x, float _y) :
					Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)), 
					TIME_BETWEEN_SHOTS(config.getFloat(KEY_SHOTS)) {}

ChainGunItem::ChainGunItem(float _x, float _y, TextureID texture, int _value,
							float _radius, float time_between_shots) :
					Item(_x, _y, texture, _value,_radius),
					TIME_BETWEEN_SHOTS(time_between_shots) {}

void ChainGunItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) throw WeaponItemException("Can't equip"
																" weapon.");

	action.equip(new ChainGun(this->TIME_BETWEEN_SHOTS, this->texture,
								this->collider.getRadius()));
}

ChainGunItem::~ChainGunItem() {}
