#include "SlidingSurface.h"
#include "GameConstants.h"
#include "../server_src/PlayerActions.h"

SlidingSurface::SlidingSurface(int _x, int _y, int _dir_x, int _dir_y,
                    int _surface_type, float _moving_time, bool is_locked,
                    int _opened_time) : 
                ManualDoor(_x, _y, _dir_x, _dir_y, _surface_type,
                        _moving_time, is_locked),
                opened_time(_opened_time) {}

void SlidingSurface::update(Map& map, const std::vector<Player*> players) {
    _updateElapsedFraction();

    if (this->state == SLIDER_OPENED && elapsed_fraction > 1) {
        if (!ManualDoor::isPlayerBlockingDoor(players)) {
            this->state = SLIDER_CLOSING;
            this->timer.start();
            map.set(this->x, this->y, this->surface_type);
        }

    } else if (this->state == SLIDER_CLOSING && elapsed_fraction > 1) {
        this->state = this->surface_type;

    } else if (this->state == SLIDER_OPENING && elapsed_fraction > 1) {
        this->state = SLIDER_OPENED;
        map.set(this->x, this->y, SLIDER_OPENED);
        this->timer.start();
    }
}

void SlidingSurface::interact(Key& key) {
    if (this->state == this->surface_type) {
        if (locked && key.has()) {
            this->state = SLIDER_OPENING;
            this->timer.start();
            locked = false;
            key.used();
        } else if (!locked) {
            this->state = SLIDER_OPENING;
            this->timer.start();
        }
    }
}

// Actualiza la fraccion de tiempo transcurrido del lapso.
void SlidingSurface::_updateElapsedFraction() {
    if (state == SLIDER_OPENED){
        this->elapsed_fraction = this->timer.getTime()/this->opened_time;
        return;
    }

    ManualDoor::_updateElapsedFraction();
}

SlidingSurface::~SlidingSurface() {}



