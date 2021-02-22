#include "ChainGunItem.h"
#include "../Weapons/ChainGun.h"
#include "../../common_src/Exceptions/ItemException.h"

#define KEY_SHOTS "time_between_shots"

ChainGunItem::ChainGunItem(const Configuration& config, float _x, float _y) :
					Item(_x, _y, ChaingunItem, CHAIN_GUN,
						config.getFloat(KEY_RADIUS)), 
					TIME_BETWEEN_SHOTS(config.getFloat(KEY_SHOTS)) {}

ChainGunItem::ChainGunItem(float _x, float _y, float _radius,
						float time_between_shots) :
					Item(_x, _y, ChaingunItem, CHAIN_GUN, _radius),
					TIME_BETWEEN_SHOTS(time_between_shots) {}

void ChainGunItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) throw ItemException("Can't equip"
																" weapon.");

	action.equip(new ChainGun(this->TIME_BETWEEN_SHOTS,
							this->collider.getRadius()));
}

ChainGunItem::~ChainGunItem() {}
