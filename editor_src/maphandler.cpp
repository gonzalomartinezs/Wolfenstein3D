#include "maphandler.h"
#include "mainwindow.h"
#include "itemList.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QPen>

MapHandler::MapHandler ( const IconsContainer& container,const std::string& name ,
                         unsigned x ,unsigned y, QWidget *parent) :
     QWidget(parent), map(x,y),icons(container) {
    setAcceptDrops(true);
    map.setName(name);
    setMinimumSize(x*ITEMSIZE, y*ITEMSIZE);
    setMaximumSize(x*ITEMSIZE, y*ITEMSIZE);
}

void MapHandler::paintEvent (QPaintEvent *event) {
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

void MapHandler::dragEnterEvent(QDragEnterEvent *event) {
    if ( event->mimeData()->hasFormat( ItemList::editorMimeType() ) )
        event->accept();
    else
        event->ignore();
}

void MapHandler::dragLeaveEvent(QDragLeaveEvent *event) {
    QRect updateRect = this->focused;
    this->focused = QRect();
    update(updateRect);
    event->accept();
}


void MapHandler::dragMoveEvent(QDragMoveEvent *event) {
    QRect updateRect = focused.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat(ItemList::editorMimeType())
        && map.isEmpty(targetCoordinate( event->pos() ) ) ) {

        this->focused = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        this->focused = QRect();
        event->ignore();
        // emit showOccupiedPosition();
    }
    update(updateRect);
}

void MapHandler::dropEvent(QDropEvent *event) {

    if ( event->mimeData()->hasFormat(ItemList::editorMimeType())
        && map.isEmpty(targetCoordinate( event->pos() ) ) ) {

        QByteArray pieceData = event->mimeData()->data(ItemList::editorMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        MapElement element;
        element.rect = targetSquare(event->pos());
        int auxInt;
        dataStream  >> auxInt;

        element.id = (Editor_icon) auxInt;
        map.add(targetCoordinate(event->pos() ) ,element);

        focused = QRect();
        update(element.rect);

        event->setDropAction(Qt::MoveAction);
        event->accept();
        /*if (piece.location == piece.rect.topLeft() / pieceSize()) {
            inPlace++;
            if (inPlace == 25)
                emit puzzleCompleted();
        }*/
        } else {
        focused = QRect();
        event->ignore();
        // emit showOccupiedPosition();
        }
}


void MapHandler::mousePressEvent(QMouseEvent *event) {
    Coordinate coor = targetCoordinate(event->pos());
    QRect square = targetSquare(event->pos());

    if (map.isEmpty(targetCoordinate(event->pos()))) return;

    MapElement element = map.get(coor);
    map.remove(coor);

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << element.id;
    QPixmap pixmap = icons.getIcon(element.id);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ItemList::editorMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) != Qt::MoveAction) {
        map.add(coor,element);
        //elements.insert(found, element);
        update(targetSquare(event->pos()));

        /*if (piece.location == square.topLeft() / pieceSize())
            inPlace++;*/
    }
}


const QRect MapHandler::targetSquare(const QPoint &p) const {

    return QRect(QPoint( (p.x()/ITEMSIZE) * ITEMSIZE,
                        (p.y()/ITEMSIZE ) * ITEMSIZE),
                 QSize(ITEMSIZE, ITEMSIZE));
}

const Coordinate MapHandler::targetCoordinate(const QPoint& position) const {

    return ( Coordinate ( (targetSquare(position).left() / ITEMSIZE),
                          targetSquare(position).top() /ITEMSIZE ) );
}

const Map& MapHandler::getMap() {
    return map;
}

void MapHandler::loadElements(std::list<MapElement>& in){
    for(auto &i : in){
        Coordinate coor(i.calculateX(), i.calculateY());
        if( map.inRange(coor) ) {
            map.add(coor, i);
        }
    }
}

void MapHandler::resizeMap (int x, int y, std::string inName) {
    printf("se llamo");
    setMinimumSize(x*ITEMSIZE, y*ITEMSIZE);
    setMaximumSize(x*ITEMSIZE, y*ITEMSIZE);
    this->map.resizeMap(x, y);
    this->map.setName(inName);
}

