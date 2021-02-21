#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H

#include "Collider.h"

class RectCollider {
private:
	float x, y;
	float width, height;
public:
	RectCollider(float _x, float _y, float _width, float _height);
	// Devuelve true si colisiona, false en caso contrario
	bool collidesWith(const Collider& collider);
	~RectCollider();
};

#endif