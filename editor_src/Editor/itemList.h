#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>
#include <vector>
#include "mapelement.h"

class ItemList : public QListWidget
{
    Q_OBJECT
public:
    explicit ItemList(int pieceSize,std::vector<MapElement>& elements, QWidget *parent = nullptr);
private:
    void loadImages();
    int itemSize;
    std::vector<MapElement>& elements;
};

#endif // ITEMLIST_H
