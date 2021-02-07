#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QPoint>
#include "item.h"

class MapElement
{
public:
    MapElement();
    int id;
    QRect rect;
    MapElement(MapElement &in){
        rect = in.rect;
        id = in.id;
        pixmap = in.pixmap;
    }

    MapElement(MapElement &&in){
        rect = in.rect;
        id = in.id;
        pixmap = in.pixmap;
    }

    MapElement(const MapElement &in){
        rect = in.rect;
        id = in.id;
        pixmap = in.pixmap;
    }
    MapElement& operator=(const MapElement& in){
        rect = in.rect;
        id = in.id;
        pixmap = in.pixmap;
        return *this;
    }

};

#endif // MAPELEMENT_H
