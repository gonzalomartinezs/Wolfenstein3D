#include "coordinate.h"

Coordinate::Coordinate(unsigned x, unsigned y):x(x), y(y) {

}


unsigned Coordinate::getX()const{
    return x;
}

unsigned Coordinate::getY()const{
    return y;
}

bool Coordinate::operator==(const Coordinate& r){
    return (x == r.x && y ==r.y);
}

std::string Coordinate::toString()const{
    return (std::to_string(x)+","+std::to_string(y));
}

bool Coordinate::inRange(Map* map)const{ //Contamos desde cero.
    return (this->x < map.getX() && this->y < map.getY() );
}
