#include "MachineGunItem.h"
#include "../server_src/Weapons/MachineGun.h"

#define KEY_SHOTS "time_between_shots"
#define KEY_BURSTS "time_between_bursts"
#define KEY_BULLETS "bullets_per_burst"

MachineGunItem::MachineGunItem(const Configuration& config, float _x,
								float _y) :
					Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)),
						TIME_BETWEEN_SHOTS(config.getFloat(KEY_SHOTS)),
                        TIME_BETWEEN_BURSTS(config.getFloat(KEY_BURSTS)),
                        BULLETS_PER_BURST(config.getInt(KEY_BULLETS)) {}

void MachineGunItem::equipTo(PlayerActions& action) {
	if(action.hasWeapon(this->value)) throw "Can't equip weapon.";

	action.equip(new MachineGun(this->TIME_BETWEEN_SHOTS,
								this->TIME_BETWEEN_BURSTS,
								this->BULLETS_PER_BURST));
}

MachineGunItem::~MachineGunItem() {}