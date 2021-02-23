#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

#include "itemList.h"

ItemList::ItemList(QWidget *parent)
    : QListWidget(parent) {
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(ITEMSIZE, ITEMSIZE));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    this->setStyleSheet(
            "QListWidget::item {"
            "border-style: solid;"
            "border-width:1px;"
            "border-color:white;"
            "background-color: black;"
            "}"
            "QListWidget::item:selected {"
            "background-color: darkRed;"
            "}"
            "QListWidget{"
            "background-color: grey;"
            "}");
}

void ItemList::loadList(const IconsContainer& inContainer) {
    inContainer.loadItemList(*this);
}

void ItemList::startDrag(Qt::DropActions ) {
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    int id = item->data(Qt::UserRole+1).toInt();

    dataStream << id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ItemList::editorMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);
    drag->exec(Qt::MoveAction);
}

void ItemList::addIcon(const int &key, const QPixmap &icon) {

    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(icon);
    pieceItem->setData(Qt::UserRole, QVariant(icon));
    pieceItem->setData(Qt::UserRole+1, key);
    pieceItem->setFlags(Qt::ItemIsEnabled |
                        Qt::ItemIsSelectable |
                        Qt::ItemIsDragEnabled);
}