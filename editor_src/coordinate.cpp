
#include "coordinate.h"
#include "map.h"

Coordinate::Coordinate(unsigned x, unsigned y):x(x), y(y) {

}


unsigned Coordinate::getX()const {
    return x;
}

unsigned Coordinate::getY()const {
    return y;
}

bool Coordinate::operator==(const Coordinate& r) const{
    return (x == r.x && y ==r.y);
}

std::string Coordinate::toString()const {
    return (std::to_string(x)+","+std::to_string(y));
}

Coordinate &Coordinate::operator=(const Coordinate &in) {
    this->x = in.x;
    this->y = in.y;
    return *this;
}
