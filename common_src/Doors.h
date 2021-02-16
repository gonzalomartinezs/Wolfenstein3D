#ifndef DOORS_H
#define DOORS_H

#include <vector>
#include "Map.h"
#include "SlidingSurface.h"

class Doors {
private:
	std::vector<SlidingSurface> doors;
public:
	Doors(const Map& map);
	SlidingSurface& operator[](const size_t i);
	size_t size() const;
	~Doors();
};

#endif
