#ifndef CHAINGUNITEM_H
#define CHAINGUNITEM_H

#include "Item.h"
#include "Configuration.h"

class ChainGunItem : public Item {
private:
	const float TIME_BETWEEN_SHOTS;
public:
	ChainGunItem(const Configuration& config, float _x, float _y);
	void equipTo(PlayerActions& action) override;
	~ChainGunItem();
};

#endif
