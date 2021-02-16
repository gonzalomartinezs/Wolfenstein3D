#include "Doors.h"
#include "GameConstants.h"

#define WALL 1
#define DOOR 2

Doors::Doors(const Map& map) {
	long int n_rows = map.get_n_row(), n_cols = map.get_n_col();

	for (long int i = 0; i < n_rows; ++i) {
		for (long int j = 0; j < n_cols; ++j) {
			if (map.get(i, j) == DOOR) {
				int dir_x = 0, dir_y = 0;
				Doors::_calculateDirection(map, i, j, &dir_x, &dir_y);
				this->doors.emplace_back(i, j, dir_x, dir_y, DOOR,
										MOVING_DOOR_TIME);
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

void Doors::_calculateDirection(const Map& map, long x, long y,
								int* dir_x, int* dir_y) {
	if ((map.get(x + 1, y) == WALL) && (map.get(x - 1, y) == WALL)) {
		(*dir_y) = 1;
	} else {
		(*dir_x) = 1;
	}
}

Doors::~Doors() {}
