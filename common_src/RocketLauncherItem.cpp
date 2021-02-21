#include "RocketLauncherItem.h"
//#include "../server_src/Weapons/RocketLauncher.h"
#include "Exceptions/ItemException.h"

RocketLauncherItem::RocketLauncherItem(const Configuration& config, float _x,
									float _y, std::vector<Rocket>& _rockets) :
					Item(_x, _y, RPGItem, config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)), 
					rockets(_rockets) {}

RocketLauncherItem::RocketLauncherItem(float _x, float _y, TextureID _texture,
								int _value, float _radius,
								std::vector<Rocket>& _rockets) :
								Item(_x, _y, _texture, _value, _radius),
								rockets(_rockets) {}

void RocketLauncherItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) {
		throw ItemException("Can't equip weapon.");
	}

//	action.equip(new RocketLauncher(this->rockets,
//		 							this->texture,
//	 								this->collider.getRadius()));
}

RocketLauncherItem::~RocketLauncherItem() {}
