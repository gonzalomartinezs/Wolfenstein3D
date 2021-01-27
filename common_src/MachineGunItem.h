#ifndef MACHINEGUNITEM_H
#define MACHINEGUNITEM_H

#include "Item.h"

class MachineGunItem : public Item {
public:
	MachineGunItem(float _x, float _y, TextureID _texture, int _value);
	void equipTo(PlayerActions& action) override;
	~MachineGunItem();
};

#endif