#include "mapelement.h"

#define ITEMSIZE 50 // HACER EL .H COMUN


MapElement::MapElement() {

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

Editor_icon MapElement::getId() const{
    return id;
}

const QRect& MapElement::getRect() const{
    return rect;
}

int MapElement::calculateX() const{
    return (rect.left() / ITEMSIZE);
}

int MapElement::calculateY() const{
    return (rect.top() / ITEMSIZE);
}

MapElement::MapElement(const Editor_icon &id, const QRect& rect) {
    this->id = id;
    this->rect = rect;
}
