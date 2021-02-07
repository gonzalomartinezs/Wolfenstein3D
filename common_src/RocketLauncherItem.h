#ifndef ROCKETLAUNCHERITEM_H
#define ROCKETLAUNCHERITEM_H

#include "Item.h"

class RocketLauncherItem : public Item {
public:
	RocketLauncherItem(const Configuration& config, float _x, float _y);
	void equipTo(PlayerActions& action);
	~RocketLauncherItem();
};

#endif
