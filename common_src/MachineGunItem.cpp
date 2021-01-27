#include "MachineGunItem.h"
#include "../server_src/Weapons/MachineGun.h"

MachineGunItem::MachineGunItem(float _x, float _y, TextureID _texture,
							int _value) : Item(_x, _y, _texture, _value) {}

void MachineGunItem::equipTo(PlayerActions& action) {
	if(!action.hasWeapon(this->value)) throw "Can't equip weapon";

	action.equip(new MachineGun());
}

MachineGunItem::~MachineGunItem() {}