#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include <QPoint>
#include "item.h"

class MapElement
{
public:
    MapElement(Item& in);
    Item& item;
    QRect rect;
};

#endif // MAPELEMENT_H
