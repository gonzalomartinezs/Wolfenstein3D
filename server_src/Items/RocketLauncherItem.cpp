#include "RocketLauncherItem.h"
#include "../Weapons/RocketLauncher.h"
#include "../../common_src/Exceptions/ItemException.h"

#define KEY_MOVE_SPEED "move_speed"
#define KEY_SIZE "size"
#define KEY_MAX_DAMAGE "max_damage"
#define KEY_MAX_DAMAGE_DISTANCE "max_damage_distance"

RocketLauncherItem::RocketLauncherItem(const Configuration& config, float _x,
							float _y, std::vector<Rocket>& _rockets) :
		Item(_x, _y, RPGItem, ROCKET_LAUNCHER,
			config.getFloat(KEY_RADIUS)), 
		rockets(_rockets), 
		ROCKET_MOVE_SPEED(config.getFloat(KEY_MOVE_SPEED)),
		ROCKET_SIZE(config.getFloat(KEY_SIZE)),
		ROCKET_MAX_DAMAGE(config.getFloat(KEY_MAX_DAMAGE)),
		ROCKET_MAX_DAMAGE_DISTANCE(config.getFloat(KEY_MAX_DAMAGE_DISTANCE)) {}

RocketLauncherItem::RocketLauncherItem(float _x, float _y, float _radius,
						std::vector<Rocket>& _rockets,float rocket_move_speed,
						float rocket_size, float rocket_max_damage,
						float rocket_max_damage_distance) :
		Item(_x, _y, RPGItem, ROCKET_LAUNCHER, _radius),
		rockets(_rockets), ROCKET_MOVE_SPEED(rocket_move_speed),
		ROCKET_SIZE(rocket_size), ROCKET_MAX_DAMAGE(rocket_max_damage),
		ROCKET_MAX_DAMAGE_DISTANCE(rocket_max_damage_distance) {}

void RocketLauncherItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) {
		throw ItemException("Can't equip weapon.");
	}

	action.equip(new RocketLauncher(this->ROCKET_MOVE_SPEED, this->ROCKET_SIZE,
					this->ROCKET_MAX_DAMAGE, this->ROCKET_MAX_DAMAGE_DISTANCE,
					this->rockets, this->collider.getRadius()));
}

RocketLauncherItem::~RocketLauncherItem() {}
