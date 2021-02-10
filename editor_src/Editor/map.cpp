#include "coordinate.h"
#include "map.h"
#include "mainwindow.h"

Map::Map(const unsigned& x, const unsigned& y): x(x), y(y) {
    std::string name = "-";
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

bool Map::inRange(const Coordinate& coor){
    return coor.inRange(this);
}

const MapElement& Map::get(const Coordinate& coor)const{
   return (this->matrix.at( coor.toString() ) );
}

std::list<MapElement> Map::getElements() const{
    std::list< MapElement> elementList;
    for(auto &kv : this->matrix){
        elementList.push_back( (kv.second) ) ;
    }
    return elementList;
}

const MapElement& Map::get(const QPoint& point) const {
    QRect rect(point / ITEMSIZE * ITEMSIZE,
               QSize(ITEMSIZE, ITEMSIZE));
     Coordinate coor( (rect.left() / ITEMSIZE), (rect.top() /ITEMSIZE ) );
    return ( this->matrix.at( coor.toString() ) );
}

const std::string& Map::getName() const {
    return name;
}

void Map::setName (const std::string& inName) {
    name = inName;
}
