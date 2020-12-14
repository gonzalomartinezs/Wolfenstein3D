#ifndef FOOD_H
#define FOOD_H

#include "Item.h"

class Food : public Item {
public:
	Food(float _x, float _y, TextureID& _texture, int _value);
	void equipTo(PlayerAttributes& attributes) override;
	~Food();
};

#endif
