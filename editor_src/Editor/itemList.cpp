#include "itemList.h"

ItemList::ItemList(int pieceSize,std::vector<Item>& x , QWidget *parent)
    : QListWidget(parent), itemSize(pieceSize), items(x) {
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(pieceSize, pieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    this->loadImages();
}

void ItemList::loadImages(){

    for (auto &i : items){
        QListWidgetItem *pieceItem = new QListWidgetItem(this);
        pieceItem->setIcon(QIcon(i.pixmap));
        pieceItem->setData(Qt::UserRole, QVariant(i.pixmap));
        //pieceItem->setData(Qt::UserRole+1, location);
        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    }
}
