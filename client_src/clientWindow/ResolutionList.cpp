//
// Created by riedel on 22/2/21.
//

#include "ResolutionList.h"

ResolutionList::ResolutionList(QWidget *parent) : QListWidget(parent) {
    setViewMode(QListView::ListMode);
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    this->setMaximumSize(90,180);
    addItem(Resolution(320, 240));
    addItem(Resolution(512, 384));
    addItem(Resolution(640, 480));
    addItem(Resolution(800, 600));
    addItem(Resolution(850, 480));
    addItem(Resolution(1280, 720));
}

void ResolutionList::addItem(const Resolution &in) {
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setText ( QString(in.toString().c_str() ) );
    pieceItem->setData(Qt::UserRole, in.getX() );
    pieceItem->setData(Qt::UserRole+1, in.getY() );
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    setCurrentItem(pieceItem); // Tener el ultimo por default.
}

Resolution ResolutionList::getSelected() {
    QListWidgetItem * item = this->selectedItems()[0];
    int x = item->data(Qt::UserRole).toInt();
    int y = item->data(Qt::UserRole+1).toInt();
    return Resolution(x, y);
}
