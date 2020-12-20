#ifndef ITEM_H
#define ITEM_H

#include "../common_src/Positionable.h"
#include "../server_src/PlayerAttributes.h"

//class Collider;

class Item : public Positionable {
protected:
	int value;
public:
	Item(float _x, float _y, TextureID& _texture, int _value);
	virtual int operator+(int other_value) const = 0;
	virtual void equipTo(PlayerAttributes& attributes) = 0;
//	bool collidesWith(const Collider& other);
	virtual ~Item();
};

#endif
