#ifndef MANUALDOOR_H
#define MANUALDOOR_H

#include "Timer.h"
#include "Map.h"
#include "Positionable.h"
#include "Collider.h"
#include "RectCollider.h"
#include "../server_src/Key.h"

class Player;

class ManualDoor : public Positionable {
private:
	const int dir_x, dir_y;
	uint8_t state;
	const int surface_type;
	const float moving_time;
	float elapsed_fraction;
	bool locked;
	RectCollider collider;
	Timer timer;
public:
	ManualDoor(int _x, int _y, int _dir_x, int _dir_y, int _surface_type,
				float _moving_time, bool is_locked);
	void update(Map& map, const std::vector<Player*> players);
	uint8_t getState() const;
	void interact(Key& key);
	bool collidesWith(const Collider& other_collider);
	~ManualDoor();
private:
	bool isPlayerBlockingDoor(const std::vector<Player*> players);
	void _updateElapsedFraction();
};

#endif
