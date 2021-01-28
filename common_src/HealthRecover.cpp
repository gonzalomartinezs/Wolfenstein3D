#include "HealthRecover.h"
#include "Exceptions/HealthRecoverException.h"

#define MAX_HEALTH 50

HealthRecover::HealthRecover(float _x, float _y, TextureID _texture,
							int _value, float radius) :
							Item(_x, _y, _texture, _value, radius) {}

void HealthRecover::equipTo(PlayerActions& action) {
	action.use(this);
}

int HealthRecover::operator+(int health) const {
	if (health > MAX_HEALTH) throw HealthRecoverException("Can't recover"
														"health, max health"
														"reached.");

	int new_health = this->value + health;

	if (new_health > MAX_HEALTH) new_health = MAX_HEALTH;

	return new_health;
}

HealthRecover::~HealthRecover() {}