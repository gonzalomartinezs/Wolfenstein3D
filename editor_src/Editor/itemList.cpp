#include "itemList.h"

ItemList::ItemList(int pieceSize,std::vector<MapElement>& elements , QWidget *parent)
    : QListWidget(parent), itemSize(pieceSize), elements(elements) {
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(pieceSize, pieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    this->loadImages();
}
void ItemList::loadImages(){

    for (auto &i : elements){
        QListWidgetItem *pieceItem = new QListWidgetItem(this);
        pieceItem->setIcon(QIcon(i.pixmap));
        pieceItem->setData(Qt::UserRole, QVariant(i.pixmap));
        //pieceItem->setData(Qt::UserRole+1, location);
        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    }
}
