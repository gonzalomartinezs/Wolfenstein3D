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

void ChainGunItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) throw WeaponItemException("Can't equip"
																" weapon.");

	action.equip(new ChainGun(this->TIME_BETWEEN_SHOTS));
}

ChainGunItem::~ChainGunItem() {}