#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include "iconscontainer.h"
#include <QRect>


class MapElement {
public:
    MapElement();
    Editor_icon id;
    QRect rect;
    MapElement(MapElement &in);

    MapElement(MapElement &&in);

    MapElement(const MapElement &in);

    MapElement& operator=(const MapElement& in);
    Editor_icon getId()const;
    const QRect& getRect() const;
    int calculateX() const;
    int calculateY() const;
};

#endif // MAPELEMENT_H
