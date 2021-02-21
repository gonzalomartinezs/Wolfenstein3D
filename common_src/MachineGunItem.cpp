#include "MachineGunItem.h"
#include "../server_src/Weapons/MachineGun.h"
#include "Exceptions/ItemException.h"

#define KEY_SHOTS "time_between_shots"
#define KEY_BURSTS "time_between_bursts"
#define KEY_BULLETS "bullets_per_burst"

MachineGunItem::MachineGunItem(const Configuration& config, float _x,
								float _y) :
					Item(_x, _y, MachinegunItem, MACHINE_GUN,
						config.getFloat(KEY_RADIUS)),
						TIME_BETWEEN_SHOTS(config.getFloat(KEY_SHOTS)),
                        TIME_BETWEEN_BURSTS(config.getFloat(KEY_BURSTS)),
                        BULLETS_PER_BURST(config.getInt(KEY_BULLETS)) {}

MachineGunItem::MachineGunItem(float _x, float _y, float radius,
						float time_between_shots,
						float time_between_bursts,
						int bullets_per_burst) :
 					Item(_x, _y, MachinegunItem, MACHINE_GUN, radius),
 						TIME_BETWEEN_SHOTS(time_between_shots),
                        TIME_BETWEEN_BURSTS(time_between_bursts),
                        BULLETS_PER_BURST(bullets_per_burst) {}

void MachineGunItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) {
		throw ItemException("Can't equip weapon.");;
	}

	action.equip(new MachineGun(this->TIME_BETWEEN_SHOTS,
								this->TIME_BETWEEN_BURSTS,
								this->BULLETS_PER_BURST,
								this->collider.getRadius()));
}

MachineGunItem::~MachineGunItem() {}
