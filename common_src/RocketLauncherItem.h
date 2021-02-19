#ifndef ROCKETLAUNCHERITEM_H
#define ROCKETLAUNCHERITEM_H

#include "Item.h"
#include "../server_src/Weapons/Rocket.h"

class RocketLauncherItem : public Item {
private:
	std::vector<Rocket>& rockets;
public:
	RocketLauncherItem(const Configuration& config, float _x, float _y,
						std::vector<Rocket>& _rockets);
	RocketLauncherItem(float _x, float _y, TextureID _texture,
					int _value, float _radius, std::vector<Rocket>& _rockets);
	void equipTo(PlayerActions& action) override;
	~RocketLauncherItem();
};

#endif
