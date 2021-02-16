#ifndef DOORS_H
#define DOORS_H

#include <vector>
#include "Map.h"
#include "ManualDoor.h"

class Doors {
private:
	std::vector<ManualDoor> doors;
public:
	Doors(const Map& map);
	ManualDoor& operator[](const size_t i);
	size_t size() const;
	~Doors();
private:
	void _calculateDirection(const Map& map, long x, long y,
							int* dir_x, int* dir_y);
};

#endif
