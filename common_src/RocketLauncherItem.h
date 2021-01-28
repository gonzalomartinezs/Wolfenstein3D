#ifndef ROCKETLAUNCHERITEM_H
#define ROCKETLAUNCHERITEM_H

#include "Item.h"

class RocketLauncherItem : public Item {
public:
	RocketLauncherItem(float _x, float _y, TextureID _texture,
						int _value, float radius);
	void equipTo(PlayerActions& action);
	~RocketLauncherItem();
};

#endif
