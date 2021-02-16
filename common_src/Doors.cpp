#include "Doors.h"

Doors::Doors(const Map& map) : doors(map.getSlidingSurfaces()) {}

SlidingSurface& Doors::operator[](const size_t i) {
	return this->doors[i];
}

size_t Doors::size() const {
	return this->doors.size();
}

Doors::~Doors() {}
