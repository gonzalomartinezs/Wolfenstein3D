#ifndef BLOOD_H
#define BLOOD_H

#include "HealthRecover.h"

class Blood : public HealthRecover {
public:
	Blood(float _x, float _y, TextureID& _texture, int _value);
	int operator+(int health) const override;
	~Blood();
};

#endif
