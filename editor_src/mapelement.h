#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QRect>

class MapElement {
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
    int calculateX() const;
    int calculateY() const;
};

#endif // MAPELEMENT_H
