#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
 private:
    const unsigned x;
    const unsigned y;
 public:
    Coordinate(unsigned x, unsigned y);
    unsigned getX();
    unsigned getY();
};

#endif // COORDINATE_H
