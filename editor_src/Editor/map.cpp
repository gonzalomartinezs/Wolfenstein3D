#include "map.h"

Map::Map(const unsigned& x, const unsigned& y): x(x), y(y)
{

}


bool Map::isEmpty(const Coordinate &cor) const{
    if(matrix.find(cor.toString()) == matrix.end() ){
        return true;
    }
    return false;
}

void Map::add(const Coordinate& cor, const MapElement& element){
    if( this->isEmpty(cor) ) //agregar si esta en rango
        this->matrix.insert({cor.toString(),element});
}

void Map::remove(const Coordinate& cor){
    if( !this->isEmpty(cor)) {
        matrix.erase(cor.toString());
    }
}

unsigned Map::getX() const{
    return this->x;
}

unsigned Map::getY() const {
    return this->y;
}

bool Map::inRange(const Coordinate& cor)const{
    cor.
}

