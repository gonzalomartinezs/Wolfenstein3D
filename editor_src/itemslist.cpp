#include "itemslist.h"

ItemsList::ItemsList(QWidget *parent ): QListWidget(parent){
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(100, 100));
   //setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void ItemsList::add(const QPixmap &pixmap)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    //pieceItem->setData(Qt::UserRole+1, location); ojo con esto, ver posicion.
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}
