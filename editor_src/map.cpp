
#include "map.h"
#include  "mapelement.h"
#include "coordinate.h"

Map::Map(const unsigned& x, const unsigned& y): x(x), y(y) {
    std::string name = "-";
    this->setPerimeter();
}

bool Map::isEmpty(const Coordinate &coor) const{
    if(matrix.find(coor.toString()) == matrix.end() ){
        return true;
    }
    return false;
}

void Map::add(const Coordinate& coor, const MapElement& element){
    if( this->inRange(coor)  ) {
        if( !this->isEmpty(coor) ) {
            remove(coor);
        }
        this->matrix.insert({coor.toString(),element});
    }
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

bool Map::inRange(const Coordinate& coor) const{
    return (coor.getX() < x && coor.getY() < y);
}

const MapElement& Map::get(const Coordinate& coor)const{
   return ( this->matrix.at( coor.toString() ) );
}

std::list<MapElement> Map::getElements() const{
    std::list< MapElement> elementList;
    for(auto &kv : this->matrix){
        if ( inRange ( kv.second.getCoor() ) ) {
            elementList.push_back( (kv.second) ) ;
        }
    }
    return elementList;
}


const std::string& Map::getName() const {
    return name;
}

void Map::setName (const std::string& inName) {
    name = inName;
}

void Map::resizeMap(int _x, int _y) {
    this->clearPerimeter();
    x = _x, y = _y;
    this->setPerimeter();
}

unsigned Map::getNumberOfPlayers() const {
    unsigned i = 0;
    for(auto &kv : this->matrix){
        if( inRange ( kv.second.getCoor() ) )
            if(kv.second.getId() == Spawn) i++;
    }
    return i;
}


void Map::setPerimeter() {
    std::list<Coordinate> peri = calculatePerimeter();
    for (const auto &i : peri){
        this->add(i,MapElement(Wall0,i));
    }
}

void Map::clearPerimeter() {
    std::list<Coordinate> peri = calculatePerimeter();
    for (const auto &i : peri){
        this->remove(i);
    }
}

bool Map::isBorder(const Coordinate& coor) const{
    if (coor.getX() == (x-1)) return true;
    if (coor.getX() == 0) return true;
    if((coor.getY() == (y-1))) return true;
    if((coor.getY() == 0)) return true;
    return false;
}

std::list<Coordinate> Map::calculatePerimeter() const {
    std::list<Coordinate> list;
    for (int i = 0; i < x ; ++i) {
        for (int j = 0; j < y; ++j) {
            Coordinate aux(i,j);
            if(isBorder(aux)) list.emplace_back(aux);
        }
    }
    return list;
}

