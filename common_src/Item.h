#ifndef ITEM_H
#define ITEM_H

#include "../common_src/Positionable.h"
#include "../server_src/PlayerAttributes.h"

class Item : public Positionable {
protected:
	int value;
public:
	Item(float _x, float _y, TextureID& _texture, int _value);
	virtual void equipTo(PlayerAttributes& attributes) = 0;
	~Item();
};

#endif
