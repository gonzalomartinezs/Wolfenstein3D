#include "Blood.h"
#include "../../common_src/Exceptions/HealthRecoverException.h"

#define KEY_MAX_HEALTH "max_health"

Blood::Blood(const Configuration& config, float _x, float _y) :
			HealthRecover(config, _x, _y, Blood_0),
			MAX_HEALTH_BLOOD(config.getInt(KEY_MAX_HEALTH)) {}

int Blood::operator+(int health) const {
	if (health >= this->MAX_HEALTH_BLOOD)
		throw HealthRecoverException("Can't recover health with blood");

	return (this->value + health);
}

Blood::~Blood() {}
