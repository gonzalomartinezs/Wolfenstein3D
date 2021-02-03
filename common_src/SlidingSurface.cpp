#include "SlidingSurface.h"
#include "GameConstants.h"

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





