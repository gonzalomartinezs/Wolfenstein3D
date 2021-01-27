#include "RocketLauncherItem.h"
//#include "../server_src/Weapons/RocketLauncher.h"

RocketLauncherItem::RocketLauncherItem(float _x, float _y,
										TextureID _texture, int _value) :
										Item(_x, _y, _texture, _value) {}

void RocketLauncherItem::equipTo(PlayerActions& action) {
	if(!action.hasWeapon(this->value)) throw "Can't equip weapon";

//	action.equip(new RocketLauncher());
}

RocketLauncherItem::~RocketLauncherItem() {}