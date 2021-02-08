#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QRect>
#include "coordinate.h"
#include "maphandler.h"

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
    int getId()const;
    const QRect& getRect() const;
    Coordinate calculateCoordenate() const;
};

#endif // MAPELEMENT_H
