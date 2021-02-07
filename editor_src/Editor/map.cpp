#include "map.h"

Map::Map(const unsigned& x, const unsigned& y): x(x), y(y)
{

}


bool Map::isEmpty(const Coordinate &coor) const{
    if(matrix.find(coor.toString()) == matrix.end() ){
        return true;
    }
    return false;
}

void Map::add(const Coordinate& coor, const MapElement& element){
    if( this->isEmpty(coor) ) //agregar si esta en rango
        this->matrix.insert({coor.toString(),element});
}

void Map::remove(const Coordinate& coor){
    if( !this->isEmpty(coor)) {
        matrix.erase(coor.toString());
    }
}

unsigned Map::getX() const{
    return this->x;
}

unsigned Map::getY() const {
    return this->y;
}

bool Map::inRange(const Coordinate& coor)const{
    coor.inRange(this);
}

MapElement& Map::get(const Coordinate& coor)const{
    this->matrix.at(coor.toString());
}
