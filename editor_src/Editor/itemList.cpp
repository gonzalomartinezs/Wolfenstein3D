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
