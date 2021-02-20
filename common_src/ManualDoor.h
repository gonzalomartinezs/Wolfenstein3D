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
protected:
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

	virtual void update(Map& map, const std::vector<Player*> players);

	virtual void update(int new_state);

	uint8_t getState() const;

	bool isClosed() const;

	bool isClosing() const;

	bool isOpened() const;

	bool isOpening() const;

	float getElapsedFraction() const;

	virtual void interact(Key& key);

	bool collidesWith(const Collider& other_collider);

	virtual ~ManualDoor();

protected:
	bool isPlayerBlockingDoor(const std::vector<Player*> players);
	virtual void _updateElapsedFraction();
};

#endif
