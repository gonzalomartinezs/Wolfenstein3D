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
