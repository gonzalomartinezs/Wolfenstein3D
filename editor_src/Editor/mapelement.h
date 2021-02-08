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
    MapElement(MapElement &in);

    MapElement(MapElement &&in);

    MapElement(const MapElement &in);

    MapElement& operator=(const MapElement& in);
};

#endif // MAPELEMENT_H
