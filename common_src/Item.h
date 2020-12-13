#ifndef ITEM_H
#define ITEM_H

#include "../server_src/Player.h"

class Item : public Positionable {
protected:
	int value;
public:
	Item(float _x, float _y, TextureID& _texture, int _value);
	virtual void equipTo(Player& player) = 0;
	~Item();
};

#endif
