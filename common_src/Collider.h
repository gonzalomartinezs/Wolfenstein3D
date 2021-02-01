#ifndef COLLIDER_H
#define COLLIDER_H

class Collider {
private:
	float x, y, radius;
public:
	Collider(float _x, float _y, float _radius);
	//Colisión con rectángulo.
	bool collidesWith(float _x, float _y, float width, float height) const;
	//Colisión con círculo.
	bool collidesWith(const Collider& other) const;
	~Collider();
};

#endif
