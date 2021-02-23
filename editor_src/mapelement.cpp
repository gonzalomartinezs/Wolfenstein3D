#include "mapelement.h"

#define ITEMSIZE 50 // HACER EL .H COMUN


MapElement::MapElement() {

}


MapElement::MapElement(MapElement &in){
    coor = in.coor;
    id = in.id;
}

MapElement::MapElement(MapElement &&in){
    coor = in.coor;
    id = in.id;
}

MapElement::MapElement(const MapElement &in){
    coor = in.coor;
    id = in.id;
}

MapElement& MapElement::operator=(const MapElement& in){
    coor = in.coor;
    id = in.id;
    return *this;
}

const Editor_icon& MapElement::getId() const{
    return id;
}

QRect MapElement::getRect() const {
    return QRect  ( QPoint ((coor.getX()*ITEMSIZE) ,
                            (coor.getY()*ITEMSIZE) ),
                  QSize (ITEMSIZE, ITEMSIZE) );
}

MapElement::MapElement(const Editor_icon &id, const Coordinate& coor) {
    this->id = id;
    this->coor = coor;
}

bool MapElement::operator==( const MapElement &rhs) {
    return (this->coor == rhs.coor);
}

MapElement::MapElement(const Editor_icon &id, const QRect &rect) {
    this->id = id;
    this ->coor =  Coordinate(rect.topLeft().x() /ITEMSIZE
            , rect.topLeft().y()/ITEMSIZE);
}

const Coordinate &MapElement::getCoor() const {
    return this->coor;
}
