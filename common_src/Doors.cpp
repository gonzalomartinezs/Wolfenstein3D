#include "Doors.h"
#include "GameConstants.h"
#include <cstring>

#define WALL 1

Doors::Doors(const Map& map) {
	long int n_rows = map.get_n_row(), n_cols = map.get_n_col();

	for (long int i = 0; i < n_rows; ++i) {
		for (long int j = 0; j < n_cols; ++j) {
			int value = map.get(i, j);
			if (value == DOOR) {
				int dir_x = 0, dir_y = 0;
				Doors::_calculateDirection(map, i, j, &dir_x, &dir_y);
				this->doors.emplace_back(i, j, dir_x, dir_y, DOOR,
										MOVING_DOOR_TIME, true);
			} else if (value == PASSAGE) {
				int dir_x = 0, dir_y = 0;
				Doors::_calculateDirection(map, i, j, &dir_x, &dir_y);
				this->doors.emplace_back(i, j, dir_x, dir_y, PASSAGE,
										MOVING_PASSAGE_TIME, false);
			}
		}
	}
}

ManualDoor& Doors::operator[](const size_t i) {
	return this->doors[i];
}

size_t Doors::size() const {
	return this->doors.size();
}

void Doors::loadDoorsInfo(uint8_t* msg, uint8_t &currentByte) {
    uint8_t size, state;

    size = static_cast<uint8_t>(this->doors.size());
    memcpy(msg + currentByte, &size, sizeof(uint8_t));
    currentByte += sizeof(uint8_t);

    for (size_t i = 0; i < this->doors.size(); i++) {
    	uint8_t id = static_cast<uint8_t>(i);
        memcpy(msg + currentByte, &id, sizeof(uint8_t));
        currentByte += sizeof(uint8_t);

        state = this->doors[i].getState();
        memcpy(msg + currentByte, &state, sizeof(uint8_t));
        currentByte += sizeof(uint8_t);
    }
}

void Doors::_calculateDirection(const Map& map, long x, long y,
								int* dir_x, int* dir_y) {
	if ((map.get(x + 1, y) == WALL) && (map.get(x - 1, y) == WALL)) {
		(*dir_y) = 1;
	} else {
		(*dir_x) = 1;
	}
}

Doors::~Doors() {}
