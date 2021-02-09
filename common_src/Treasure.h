#ifndef TREASURE_H
#define TREASURE_H

#include "Item.h"
#include "Configuration.h"

class Treasure : public Item {
public:
	Treasure(const Configuration& config, float _x, float _y);
	void equipTo(PlayerActions& action) override;
	~Treasure();
};

#endif
