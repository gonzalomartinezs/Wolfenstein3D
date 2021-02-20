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

	float getX();
	float getY();

	~RandomPosition();

private:
	float calculateAux();
};

#endif
