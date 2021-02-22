#ifndef BULLETITEM_H
#define BULLETITEM_H

#include "Item.h"
#include "../../common_src/Configuration.h"

class BulletItem : public Item {
private:
	const int MAX_BULLETS;
public:
	BulletItem(const Configuration& config, float _x, float _y);
	BulletItem(float x, float y, int _value, float _radius, int max_bullets);
	int operator+(int bullets) const override;
	void equipTo(PlayerActions& action) override;
	~BulletItem();
};

#endif
