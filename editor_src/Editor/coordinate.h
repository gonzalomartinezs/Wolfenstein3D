#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

class Coordinate
{
 private:
    const unsigned x;
    const unsigned y;
 public:
    Coordinate(unsigned x, unsigned y);
    unsigned getX();
    unsigned getY();
    std::string to_string();
    bool operator==(const Coordinate& r);
};

#endif // COORDINATE_H
