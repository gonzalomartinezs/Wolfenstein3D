#include "RocketLauncherItem.h"
//#include "../server_src/Weapons/RocketLauncher.h"
#include "Exceptions/WeaponItemException.h"

RocketLauncherItem::RocketLauncherItem(const Configuration& config, float _x,
									float _y) :
					Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)) {}

void RocketLauncherItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) {
		throw WeaponItemException("Can't equip weapon.");
	}

//	action.equip(new RocketLauncher());
}

RocketLauncherItem::~RocketLauncherItem() {}
