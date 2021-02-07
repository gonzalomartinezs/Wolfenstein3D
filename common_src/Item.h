#ifndef ITEM_H
#define ITEM_H

#include "Positionable.h"
#include "Collider.h"
#include "../server_src/PlayerActions.h"

#define KEY_POS_X "pos_x"
#define KEY_POS_Y "pos_y"
#define KEY_TEXTURE "texture"
#define KEY_VALUE "value"
#define KEY_RADIUS "radius"

class Item : public Positionable {
protected:
	int value;
	Collider collider;
public:
	Item(float _x, float _y, TextureID _texture, int _value, float radius);
	virtual int operator+(int other_value) const;
	virtual void equipTo(PlayerActions& action) = 0;
	bool collidesWith(const Collider& other) const;
	virtual ~Item();
};

#endif
