#ifndef COORDINATE_H
#define COORDINATE_H

#include <string>

class Coordinate {
 private:
     unsigned x;
     unsigned y;
 public:
    Coordinate(unsigned x = 0, unsigned y =0 );
    unsigned getX()const;
    unsigned getY()const;
    std::string toString()const;
    bool operator==(const Coordinate& r)const;
    //Coordinate& operator=(Coordinate);
    Coordinate& operator=(const Coordinate&);
};

#endif // COORDINATE_H
