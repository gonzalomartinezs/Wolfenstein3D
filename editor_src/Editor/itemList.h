#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>
#include <vector>
#include "item.h"

class ItemList : public QListWidget
{
    Q_OBJECT
public:
    explicit ItemList(int pieceSize,std::vector<Item>& item, QWidget *parent = nullptr);
private:
    void loadImages();
    int itemSize;
    std::vector<Item>& items;
};

#endif // ITEMLIST_H
