#ifndef HEALTHRECOVER_H
#define HEALTHRECOVER_H

#include "Item.h"
#include "../../common_src/Configuration.h"

class HealthRecover : public Item {
private:
	const int MAX_HEALTH;
public:
	HealthRecover(const Configuration& config, float _x, float _y,
				TextureID _texture);
	int operator+(int health) const override;
	void equipTo(PlayerActions& action) override;
	~HealthRecover();
};

#endif
