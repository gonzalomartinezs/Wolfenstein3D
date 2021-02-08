#include "mapelement.h"
#include "mainwindow.h"

#define ITEMSIZE 50


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

int MapElement::calculateX() const{
    return (rect.left() / ITEMSIZE);
}

int MapElement::calculateY() const{
    return (rect.top() / ITEMSIZE);
}
