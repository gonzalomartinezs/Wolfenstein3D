#ifndef COLLIDER_H
#define COLLIDER_H

class Collider {
private:
	float x, y, radius;
public:
	Collider(float _x, float _y, float _radius);
	bool collidesWith(float _x, float _y) const;
	bool collidesWith(const Collider& other) const;
	~Collider();
};

#endif
