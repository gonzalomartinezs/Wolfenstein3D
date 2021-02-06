#include "trashbin.h"

#include "mainwindow.h"
#include "itemList.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

TrashBin::TrashBin(QWidget *parent) : QWidget(parent)
{
     setAcceptDrops(true);
     QPalette pal = palette();
     this->resize(500,500);
     pal.setColor(QPalette::Background, Qt::red);
     this->setAutoFillBackground(true);
     this->setPalette(pal);
}


void TrashBin::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void TrashBin::dropEvent(QDropEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}
