#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>
#include "map.h"

class Coordinate {
 private:
    const unsigned x;
    const unsigned y;
 public:
    Coordinate(unsigned x, unsigned y);
    unsigned getX()const;
    unsigned getY()const;
    std::string toString()const;
    bool operator==(const Coordinate& r);
    bool inRange(const Map& map)const;

};

#endif // COORDINATE_H
