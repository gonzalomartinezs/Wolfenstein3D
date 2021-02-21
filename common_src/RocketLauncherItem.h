#ifndef ROCKETLAUNCHERITEM_H
#define ROCKETLAUNCHERITEM_H

#include "Item.h"
#include "../server_src/Weapons/Rocket.h"

class RocketLauncherItem : public Item {
private:
	std::vector<Rocket>& rockets;
	const float ROCKET_MOVE_SPEED, ROCKET_SIZE, ROCKET_MAX_DAMAGE,
				ROCKET_MAX_DAMAGE_DISTANCE;
public:
	RocketLauncherItem(const Configuration& config, float _x, float _y,
						std::vector<Rocket>& _rockets);
	RocketLauncherItem(float _x, float _y, float _radius,
						std::vector<Rocket>& _rockets, float rocket_move_speed,
						float rocket_size, float rocket_max_damage,
						float rocket_max_damage_distance);
	void equipTo(PlayerActions& action) override;
	~RocketLauncherItem();
};

#endif
