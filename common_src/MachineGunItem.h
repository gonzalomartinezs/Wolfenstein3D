#ifndef MACHINEGUNITEM_H
#define MACHINEGUNITEM_H

#include "Item.h"

class MachineGunItem : public Item {
private:
	const float TIME_BETWEEN_SHOTS, TIME_BETWEEN_BURSTS;
	const int BULLETS_PER_BURST;
public:
	MachineGunItem(const Configuration& config, float _x, float _y);
	MachineGunItem(float _x, float _y, TextureID texture,
					int id, float radius,
					float time_between_shots,
					float time_between_bursts,
					int bullets_per_burst);
	void equipTo(PlayerActions& action) override;
	~MachineGunItem();
};

#endif