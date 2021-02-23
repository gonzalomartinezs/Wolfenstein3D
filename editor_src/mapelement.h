#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include "iconscontainer.h"
#include "coordinate.h"
#include <QRect>

class MapElement {
public:
    MapElement();
    MapElement(const Editor_icon& id, const Coordinate& coor);
    MapElement(const Editor_icon& id, const QRect& rect);
    const Editor_icon& getId() const;
    const Coordinate& getCoor() const;
    QRect getRect() const;

    MapElement(MapElement &in);
    MapElement(MapElement &&in);
    MapElement(const MapElement &in);
    bool operator==( const MapElement& rhs);
    MapElement& operator=(const MapElement& in);
private:
    Editor_icon id;
    Coordinate coor;
};

#endif // MAPELEMENT_H
