#ifndef TREASURE_H
#define TREASURE_H

#include "Item.h"
#include "../../common_src/Configuration.h"

class Treasure : public Item {
public:
	Treasure(const Configuration& config, float _x, float _y,
			TextureID _texture);
	void equipTo(PlayerActions& action) override;
	~Treasure();
};

#endif
