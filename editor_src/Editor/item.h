#ifndef ITEM_H
#define ITEM_H

#include <QPixmap>
class Item
{
public:
    Item();
    int id;
    QPixmap pixmap;
    Item(Item &in){
        id = in.id;
        pixmap = in.pixmap;
    }
    Item(const Item &in){
        id = in.id;
        pixmap = in.pixmap;
    }
};

#endif // ITEM_H
