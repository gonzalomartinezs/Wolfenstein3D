#ifndef ROCKET_H
#define ROCKET_H

#include "../../common_src/DirectedPositionable.h"

class Player;

class Rocket : public DirectedPositionable {
public:
	Rocket(float _x, float _y, float _dir_x, float _dir_y);
//	void update(std::vector<Player*> players);
	~Rocket();	
};

#endif
