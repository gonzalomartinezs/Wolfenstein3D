#include "trashbin.h"

#include "mainwindow.h"
#include "itemList.h"
#include "iconsPaths.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

TrashBin::TrashBin(QWidget *parent) : QWidget(parent) {
     setAcceptDrops(true);
     QPalette pal = palette();
     trashIcon.load(TRASH_BIN_PATH);
     openedTrashIcon.load(OPENED_TRASH_BIN_PATH);
     isDrag = false;
     setAutoFillBackground(true);
}


void TrashBin::dragEnterEvent(QDragEnterEvent *event) {
    this->isDrag = true;
    update(this->rect());
    event->accept();
}

void TrashBin::dropEvent(QDropEvent *event) {
    event->setDropAction(Qt::MoveAction);
    this->isDrag = false;
    update(this->rect());
    event->accept();
}

void TrashBin::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    if(isDrag) {
        printDrop(event, painter);
    } else{
        printDefault(event, painter);
    }
}

void TrashBin::printDefault(const QPaintEvent *event,QPainter &painter) {
    painter.fillRect(event->rect(), Qt::darkRed);
    QPoint center = this->rect().center();
    QRect rect;
    rect.setHeight(72); rect.setWidth(72);
    rect.moveCenter(center);
    painter.drawPixmap(rect,
                       trashIcon.scaled(50,50));
}

void TrashBin::printDrop(const QPaintEvent *event, QPainter &painter) {
    painter.fillRect(event->rect(), Qt::darkBlue);
    QPoint center = this->rect().center();
    QRect rect;
    rect.setHeight(72); rect.setWidth(72);
    rect.moveCenter(center);
    painter.drawPixmap(rect,
                       openedTrashIcon.scaled(50,50));
}

void TrashBin::dragLeaveEvent(QDragLeaveEvent *event) {
    this->isDrag = false;
    update(this->rect());
    event->accept();
}

