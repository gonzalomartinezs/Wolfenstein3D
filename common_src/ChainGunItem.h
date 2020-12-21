#ifndef CHAINGUNITEM_H
#define CHAINGUNITEM_H

#include "Item.h"

class ChainGunItem : public Item {
public:
	ChainGunItem(float _x, float _y, TextureID& _texture, int _value);
	void equipTo(PlayerActions& action);
	~ChainGunItem();
};

#endif
