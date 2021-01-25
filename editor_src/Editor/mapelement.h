#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QPoint>
#include <QPixmap>

class MapElement
{
public:
    MapElement();
private:
    QPixmap pixmap;
    QRect rect;
    QPoint location;
};

#endif // MAPELEMENT_H
