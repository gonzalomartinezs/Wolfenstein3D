#include "SlidingSurface.h"
#include "GameConstants.h"
#include "../server_src/PlayerActions.h"
#include "Map.h"

SlidingSurface::SlidingSurface(int id, int x, int y, int surface_type,
                        int opened_time, int moving_time, int initial_state) :
                    id(id), pos_x(x), pos_y(y), surface_type(surface_type),
                    moving_time(moving_time), opened_time(opened_time),
                    state(initial_state), elapsed_fraction(0.0) {
    timer.start();
}

void SlidingSurface::update(int new_state) {
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

void SlidingSurface::update(Map& map) {
    if (state == SLIDER_OPENING || state == SLIDER_OPENED) {
        map.set(this->pos_x, this->pos_y, SLIDER_OPENED);
    } else {
        map.set(this->pos_x, this->pos_y, this->surface_type);
    }

    SlidingSurface::update(this->state);
}

int SlidingSurface::getState() {
    update(state);
    return state;
}

bool SlidingSurface::isOpened() const{
    return state == SLIDER_OPENED;
}

bool SlidingSurface::isOpening() const{
    return state == SLIDER_OPENING;
}

bool SlidingSurface::isClosed() const{
    return state == surface_type;
}

bool SlidingSurface::isClosing() const{
    return state == SLIDER_CLOSING;
}

float SlidingSurface::getElapsedFraction() const{
    return elapsed_fraction;
}

int SlidingSurface::getX() const{
    return pos_x;
}

int SlidingSurface::getY() const{
    return pos_y;
}

int SlidingSurface::getSurfaceType() const{
    return surface_type;
}

int SlidingSurface::getId() const{
    return this->id;
}

bool SlidingSurface::collidesWith(const Collider& collider) const {
    //Cambiar el Width y Height
    return collider.collidesWith(this->pos_x, this->pos_y, 1, 1);
}

void SlidingSurface::interact(PlayerActions* player) {
    if (this->state == SLIDER_OPENED) {
        this->state = SLIDER_CLOSING;
    } else {
        this->state = SLIDER_OPENING;
    }
}

// Actualiza la fraccion de tiempo transcurrido del lapso.
void SlidingSurface::_updateElapsedFraction() {
    if ((state == SLIDER_OPENING) || (state == SLIDER_CLOSING)){
        elapsed_fraction = timer.getTime()/moving_time;
    } else if (state == SLIDER_OPENED){
        elapsed_fraction = timer.getTime()/opened_time;
    } else {
        elapsed_fraction = 0;
    }
}





