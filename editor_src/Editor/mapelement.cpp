#include "mapelement.h"

MapElement::MapElement()
{

}


MapElement::MapElement(MapElement &in){
    rect = in.rect;
    id = in.id;
}

MapElement::MapElement(MapElement &&in){
    rect = in.rect;
    id = in.id;
}

MapElement::MapElement(const MapElement &in){
    rect = in.rect;
    id = in.id;
}

MapElement& MapElement::operator=(const MapElement& in){
    rect = in.rect;
    id = in.id;
    return *this;
}

int MapElement::getId() const{
    return id;
}

const QRect& MapElement::getRect() const{
    return rect;
}
