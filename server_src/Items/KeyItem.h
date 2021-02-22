#ifndef KEYITEM_H
#define KEYITEM_H

#include "Item.h"

class KeyItem : public Item {
public:
	KeyItem(const Configuration& config, float _x, float _y);
	KeyItem(float _x, float _y, int _radius);
	void equipTo(PlayerActions& action) override;
	~KeyItem();
};

#endif
