#include "itemList.h"

ItemList::ItemList(int pieceSize, QWidget *parent)
    : QListWidget(parent), itemSize(pieceSize) {
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(pieceSize, pieceSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void ItemList::add(const QPixmap &pixmap){
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    //pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}
