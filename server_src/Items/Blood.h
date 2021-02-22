#ifndef BLOOD_H
#define BLOOD_H

#include "HealthRecover.h"
#include "../../common_src/Configuration.h"

class Blood : public HealthRecover {
private:
	const int MAX_HEALTH_BLOOD;
public:
	Blood(const Configuration& config, float _x, float _y);
	int operator+(int health) const override;
	~Blood();
};

#endif
