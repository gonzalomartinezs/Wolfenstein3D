#include "Doors.h"
#include "GameConstants.h"
#include <cstring>

#define ID_MIN 9
#define ID_WALKABLE 0

Doors::Doors(const Map& map) {
	long int n_rows = map.get_n_row(), n_cols = map.get_n_col();

	for (long int i = 0; i < n_rows; ++i) {
		for (long int j = 0; j < n_cols; ++j) {
			int value = map.get(i, j);
			if (value > ID_MIN) {
				int dir_x = 0, dir_y = 0;
				Doors::_calculateDirection(map, i, j, &dir_x, &dir_y);
				if (value == LOCKED_DOOR) {
					this->doors.push_back(new ManualDoor(i, j, dir_x, dir_y,
										LOCKED_DOOR, MOVING_DOOR_TIME, true));
				} else if (value == PASSAGE) {
					this->doors.push_back(new ManualDoor(i, j, dir_x, dir_y,
										PASSAGE, MOVING_PASSAGE_TIME, false));
				} else if (value == AUTOMATIC_DOOR) {
					this->doors.push_back(new SlidingSurface(i, j, dir_x, dir_y,
										AUTOMATIC_DOOR, MOVING_AUTO_DOOR_TIME,
										false, TIME_BEFORE_CLOSING_AUTO_DOOR));
				}
			}
		}
	}
}

ManualDoor& Doors::operator[](const size_t i) {
	return (*this->doors[i]);
}

size_t Doors::size() const {
	return this->doors.size();
}

void Doors::loadDoorsInfo(uint8_t* msg, uint32_t &currentByte) {
    uint8_t size = static_cast<uint8_t>(this->doors.size());
    memcpy(msg + currentByte, &size, sizeof(uint8_t));
    currentByte += sizeof(uint8_t);

    for (size_t i = 0; i < this->doors.size(); i++) {
        uint8_t state = this->doors[i]->getState();
        memcpy(msg + currentByte, &state, sizeof(uint8_t));
        currentByte += sizeof(uint8_t);
    }
}

void Doors::_calculateDirection(const Map& map, long x, long y,
								int* dir_x, int* dir_y) {
	if ((map.get(x + 1, y) <= ID_WALKABLE) &&
		(map.get(x - 1, y) <= ID_WALKABLE)) {
		(*dir_x) = 1;
	} else {
		(*dir_y) = 1;
	}
}

Doors::~Doors() {
	for (size_t i = 0; i < this->doors.size(); ++i) {
		delete this->doors[i];
	}
}

