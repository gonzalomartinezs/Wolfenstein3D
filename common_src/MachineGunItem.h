#ifndef MACHINEGUNITEM_H
#define MACHINEGUNITEM_H

#include "Item.h"

class MachineGunItem : public Item {
private:
	const float TIME_BETWEEN_SHOTS, TIME_BETWEEN_BURSTS;
	const int BULLETS_PER_BURST;
public:
	MachineGunItem(const Configuration& config, float _x, float _y);
	void equipTo(PlayerActions& action) override;
	~MachineGunItem();
};

#endif