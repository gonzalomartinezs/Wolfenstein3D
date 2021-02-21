#ifndef RANDOMPOSITION_H
#define RANDOMPOSITION_H

#include <random>

class RandomPosition {
private:
	const float x, y, range_x, range_y;
	int direction;
	std::random_device rd;

public:
	RandomPosition(const float _x, const float _y);

	// Devuelven una nueva posición x, y con un offset respecto
	// de los originales
	float getX();
	float getY();

	~RandomPosition();

private:
	float calculateAux();
};

#endif
