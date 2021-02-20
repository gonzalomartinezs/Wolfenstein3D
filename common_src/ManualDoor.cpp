#include "ManualDoor.h"

#include "GameConstants.h"
#include "../server_src/Player.h"

#define SIZE 1
#define EXTRA_SIZE 0.7f

ManualDoor::ManualDoor(int _x, int _y, int _dir_x, int _dir_y,
					int _surface_type, float _moving_time, bool is_locked) :
			Positionable(_x, _y,
					static_cast<TextureID>(_surface_type)),
					dir_x(_dir_x), dir_y(_dir_y), state(_surface_type),
					surface_type(_surface_type), moving_time(_moving_time),
					elapsed_fraction(0), locked(is_locked),
			collider(this->x - (EXTRA_SIZE * this->dir_x),
					this->y - (EXTRA_SIZE * this->dir_y),
					SIZE + ((2 * EXTRA_SIZE) * this->dir_x),
					SIZE + ((2 * EXTRA_SIZE) * this->dir_y)) {}

void ManualDoor::update(Map& map, const std::vector<Player*> players) {
	_updateElapsedFraction();

	if (this->state == SLIDER_CLOSING) {
        if (!ManualDoor::isPlayerBlockingDoor(players)) {
            if (elapsed_fraction > 1) {
                this->state = surface_type;
            }

            map.set(this->x, this->y, this->surface_type);
        } else {
            this->state = SLIDER_OPENED;
        }
    } else if (this->state == SLIDER_OPENING && elapsed_fraction > 1) {
        this->state = SLIDER_OPENED;
        map.set(this->x, this->y, SLIDER_OPENED);
        timer.start();
    }

}

void ManualDoor::update(int new_state) {
	if (state == new_state){
        _updateElapsedFraction();
        if (!isClosed() && elapsed_fraction > 1){
            if (isClosing()) new_state = surface_type;
            else if (isOpening()) new_state = SLIDER_OPENED;
            else if (isOpened()) new_state = SLIDER_CLOSING;
        }
    }
    if (state != new_state) {
        state = new_state;
        if (!isClosed()) timer.start();
    }
}

bool ManualDoor::isClosed() const {
	return (this->state == this->surface_type);
}

bool ManualDoor::isClosing() const {
	return (this->state == SLIDER_CLOSING);
}

bool ManualDoor::isOpened() const {
	return (this->state == SLIDER_OPENED);
}

bool ManualDoor::isOpening() const {
	return (this->state == SLIDER_OPENING);
}

uint8_t ManualDoor::getState() const {
	return this->state;
}

float ManualDoor::getElapsedFraction() const {
    return this->elapsed_fraction;
}

void ManualDoor::interact(Key& key) {	
	if (this->state == SLIDER_OPENED) {
		this->state = SLIDER_CLOSING;
		timer.start();
	} else if (this->state == surface_type) {
		if (locked && key.has()) {
			this->state = SLIDER_OPENING;
			timer.start();
			locked = false;
			key.used();
		} else if (!locked) {
			this->state = SLIDER_OPENING;
			timer.start();
		}
	}
}

bool ManualDoor::collidesWith(const Collider& other_collider) {
	return collider.collidesWith(other_collider);
}

bool ManualDoor::isPlayerBlockingDoor(const std::vector<Player*> players) {
	RectCollider hit_collider(this->x, this->y, SIZE, SIZE);
	for (size_t i = 0; i < players.size(); ++i) {
        if (hit_collider.collidesWith(players[i]->getCollider())) {
            return true;
        }
    }

    return false;
}

void ManualDoor::_updateElapsedFraction() {
    if ((state == SLIDER_OPENING) || (state == SLIDER_CLOSING)){
        this->elapsed_fraction = this->timer.getTime()/this->moving_time;
    } else {
        this->elapsed_fraction = 0;
    }
}

ManualDoor::~ManualDoor() {}

