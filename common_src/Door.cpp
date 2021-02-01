#include "Door.h"
#include "GameConstants.h"

Door::Door(int x, int y, int moving_time, int opened_limit, int initial_state)
            : state(initial_state), pos_x(x), pos_y(y),
            door_moving_time(moving_time), door_opened_limit(opened_limit),
            fraction_remaining(0.0) {
    timer.start();
}

void Door::update(int new_state) {
    if (state == new_state){
        _updateFractionRemaining();
        if (!isClosed() && fraction_remaining > 1){
            if (isClosing()) new_state = DOOR_CLOSED;
            else if (isOpening()) new_state = DOOR_OPENED;
            else if (isOpened()) new_state = DOOR_CLOSING;
        }
    }
    if (state != new_state) {
        state = new_state;
        if (!isClosed()) timer.start();
    }
}

int Door::getState() {
    update(state);
    return state;
}

bool Door::isOpened() {
    return state == DOOR_OPENED;
}

bool Door::isOpening() {
    return state == DOOR_OPENING;
}

bool Door::isClosed() {
    return state == DOOR_CLOSED;
}

bool Door::isClosing() {
    return state == DOOR_CLOSING;
}

float Door::getFractionRemaining() {
    return fraction_remaining;
}

int Door::getX() {
    return pos_x;
}

int Door::getY() {
    return pos_y;
}

// Actualiza la fraccion de tiempo faltante para el cumplimiiento de un lapso.
void Door::_updateFractionRemaining() {
    if ((state == DOOR_OPENING) || (state == DOOR_CLOSING)){
        fraction_remaining = timer.getTime()/door_moving_time;
    } else if (state == DOOR_OPENED){
        fraction_remaining = timer.getTime()/door_opened_limit;
    } else {
        fraction_remaining = 0;
    }
}


