#include "Blood.h"
#include "Exceptions/HealthRecoverException.h"

#define MAX_HEALTH_BLOOD 11

Blood::Blood(float _x, float _y, TextureID _texture, int _value,
			float radius) : HealthRecover(_x, _y, _texture, _value, radius) {}

int Blood::operator+(int health) const {
	if (health > MAX_HEALTH_BLOOD) throw HealthRecoverException("Can't"
									"recover health with blood");

	return (this->value + health);
}

Blood::~Blood() {}