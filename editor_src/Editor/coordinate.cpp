#include "coordinate.h"

Coordinate::Coordinate(unsigned x, unsigned y):x(x), y(y) {

}


unsigned Coordinate::getX(){
    return x;
}

unsigned Coordinate::getY(){
    return y;
}

bool Coordinate::operator==(const Coordinate& r){
    return (x == r.x && y ==r.y);
}

std::string Coordinate::to_string(){
    return (std::to_string(x)+","+std::to_string(y));
}
