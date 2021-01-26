#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QPoint>
#include <QPixmap>

class MapElement
{
public:
    MapElement();
    int element;
    QPixmap pixmap;
    QRect rect;
    QPoint location;
};

#endif // MAPELEMENT_H
