#ifndef HEALTHRECOVER_H
#define HEALTHRECOVER_H

#include "Item.h"

class HealthRecover : public Item {
public:
	HealthRecover(float _x, float _y, TextureID& _texture, int _value);
	int operator+(int health) const override;
	void equipTo(PlayerActions& action) override;
	~HealthRecover();
};

#endif
