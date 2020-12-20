#ifndef TREASURE_H
#define TREASURE_H

#include "Item.h"

class Treasure : public Item {
public:
	Treasure(float _x, float _y, TextureID& _texture, int _value);
	void equipTo(PlayerAttributes& attributes);
	int operator+(int score) const override;
	~Treasure();
};

#endif
