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
     trashIcon.load("");
     //this->resize(500,500);
     pal.setColor(QPalette::Background, Qt::darkRed);
     this->setAutoFillBackground(true);
     this->setPalette(pal);
}


void TrashBin::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void TrashBin::dropEvent(QDropEvent *event) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void TrashBin::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap()
}

/*void MapHandler::paintEvent (QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::darkGreen);

    painter.setPen( QPen(Qt::gray, 1, Qt::DashDotLine, Qt::RoundCap) ) ;

    for (int i = ITEMSIZE; i < this->width(); i+=ITEMSIZE ) {
        painter.drawLine(QPoint( i, 0), QPoint(i, this->height() ) );
    }

    for (int i = ITEMSIZE; i < this->height(); i+=ITEMSIZE ) {
        painter.drawLine(QPoint( 0, i), QPoint(this->width(), i ) );
    }

    if ( focused.isValid() ) {
        painter.setBrush(QColor(255, 0, 0 ,127));
        painter.setPen(Qt::NoPen);
        painter.drawRect( focused.adjusted(0, 0, -1, -1) );
    }

    std::list < MapElement> filled = this->map.getElements();
    for (const MapElement &i : filled) {
        painter.drawPixmap(i.getRect() , this->icons.getIcon(i.getId() ) );
    }
}
 * */