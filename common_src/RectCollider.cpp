#include "RectCollider.h"

RectCollider::RectCollider(float _x, float _y, float _width, float _height) :
						x(_x), y(_y), width(_width), height(_height) {}

bool RectCollider::collidesWith(const Collider& collider) {
	return collider.collidesWith(this->x, this->y, this->width, this->height);
}

RectCollider::~RectCollider() {}