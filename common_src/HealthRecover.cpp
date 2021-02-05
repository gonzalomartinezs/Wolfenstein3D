#include "HealthRecover.h"
#include "Exceptions/HealthRecoverException.h"

#define KEY_MAX_HEALTH "max_health"

HealthRecover::HealthRecover(const Configuration& config, float _x, float _y)
					: Item(_x, _y,
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS)),
						MAX_HEALTH(config.getInt(KEY_MAX_HEALTH)) {}

void HealthRecover::equipTo(PlayerActions& action) {
	action.use(this);
}

int HealthRecover::operator+(int health) const {
	if (health >= this->MAX_HEALTH) 
		throw HealthRecoverException("Can't recover health, max health"
									" reached.");

	int new_health = this->value + health;

	if (new_health > this->MAX_HEALTH) new_health = this->MAX_HEALTH;

	return new_health;
}

HealthRecover::~HealthRecover() {}