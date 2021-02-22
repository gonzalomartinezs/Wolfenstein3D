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

bool Map::inRange(const Coordinate& coor) const{
    return coor.inRange(*this);
}

const MapElement& Map::get(const Coordinate& coor)const{
   return ( this->matrix.at( coor.toString() ) );
}

std::list<MapElement> Map::getElements() const{
    std::list< MapElement> elementList;
    for(auto &kv : this->matrix){
        if( inRange ( Coordinate (kv.second.calculateX(), kv.second.calculateY() ) ) )
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

void Map::resizeMap(int _x, int _y) {
    x = _x, y = _y;
 }

unsigned Map::getNumberOfPlayers() const{
    unsigned i = 0;
    for(auto &kv : this->matrix){
        if( inRange ( Coordinate (kv.second.calculateX(), kv.second.calculateY() ) ) )
            if(kv.second.id == Spawn) i++;
    }
    return i;
}

void Map::setOutline() {
    /*
    for (int i = 0; i < x; ++i) {
        Coordinate coor(i,0);
        this->matrix.insert ({coor.toString(),MapElement(Wall0,
                                                        QRect(QPoint(i*ITEMSIZE,0),
                                                              QSize(ITEMSIZE,ITEMSIZE)))});
    }
    for (int i = 0; i < x ; i++) {
        Coordinate coor(i,y-1);
        this->matrix.insert ({coor.toString(),MapElement(Wall0,
                                                         QRect(QPoint(i*ITEMSIZE,(y-1)*ITEMSIZE),
                                                               QSize(ITEMSIZE,ITEMSIZE)))});
    }
    for (int i = 0; i < y ; i++) {
        Coordinate coor(0,i);
        this->matrix.insert ({coor.toString(),MapElement(Wall0,
                                                         QRect(QPoint(0,i*ITEMSIZE),
                                                               QSize(ITEMSIZE,ITEMSIZE)))});
    }
    for (int i = 0; i < y ; i++) {
        Coordinate coor(x-1,i);
        this->matrix.insert ({coor.toString(),MapElement(Wall0,
                                                         QRect(QPoint((x-1)*ITEMSIZE,i*ITEMSIZE),
                                                               QSize(ITEMSIZE,ITEMSIZE)))});
    }
     */
}
