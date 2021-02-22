
#include "StringList.h"

StringList::StringList(QWidget *parent) : QListWidget(parent) {
    setViewMode(QListView::ListMode);
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    this->setMaximumSize(150,180);
}

void StringList::addItem(uint8_t key, const std::string &name) {
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setText ( name.c_str() );
    pieceItem->setData(Qt::UserRole, key);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    setCurrentItem(pieceItem); // Tener el ultimo por default.
}

uint8_t StringList::getSelected() {
    QListWidgetItem * item = this->selectedItems()[0];
    return ( item->data(Qt::UserRole).toInt() );
}




