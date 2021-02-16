#include "itemList.h"
#include "mainwindow.h" // def del tam.

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

ItemList::ItemList(QWidget *parent)
    : QListWidget(parent){
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(ITEMSIZE, ITEMSIZE));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

void ItemList::loadList(const IconsContainer& list) {
    const std::vector<QPixmap>& items = list.getIcons();

    for(unsigned i = 0; i < items.size(); i++) {
        QListWidgetItem *pieceItem = new QListWidgetItem(this);
        pieceItem->setIcon(QIcon(items[i]));
        pieceItem->setData(Qt::UserRole, QVariant(items[i]));
        pieceItem->setData(Qt::UserRole+1, i);
        pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    }
}

void ItemList::startDrag(Qt::DropActions ) {
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    int id = item->data(Qt::UserRole+1).toInt();

    dataStream << pixmap << id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ItemList::editorMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);
    drag->exec(Qt::MoveAction);
}

