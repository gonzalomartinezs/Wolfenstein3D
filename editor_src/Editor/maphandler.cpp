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
    Q_INIT_RESOURCE(editor);
    setAcceptDrops(true);
    map.setName(name);
    setMinimumSize(x*ITEMSIZE, y*ITEMSIZE);
    setMaximumSize(x*ITEMSIZE, y*ITEMSIZE);
}

void MapHandler::paintEvent (QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::darkCyan);

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
        QPixmap aux;
        dataStream >> aux >> element.id;
        // intentar hacerlo sin mandar el pixmap del otro lado.

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
        }
}


void MapHandler::mousePressEvent(QMouseEvent *event) {
    Coordinate coor = targetCoordinate(event->pos());
    QRect square = targetSquare(event->pos());

    if (map.isEmpty(targetCoordinate(event->pos()))) return;


    MapElement element = map.get(coor);
    map.remove(coor);

    update(square);

    QPixmap aux = icons.getIcon(element.id);
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << aux << element.id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ItemList::editorMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(aux);

    if (drag->exec(Qt::MoveAction) != Qt::MoveAction) {
        map.add(coor,element);
        //elements.insert(found, element);
        update(targetSquare(event->pos()));

        /*if (piece.location == square.topLeft() / pieceSize())
            inPlace++;*/
    }
}

 // cambiar a coordenadas !
const QRect MapHandler::targetSquare(const QPoint &position) const {
    return QRect(position / ITEMSIZE * ITEMSIZE,
                 QSize(ITEMSIZE, ITEMSIZE));
}

const Coordinate MapHandler::targetCoordinate(const QPoint& position) const{
    QRect rect(position / ITEMSIZE * ITEMSIZE,
               QSize(ITEMSIZE, ITEMSIZE));
    return ( Coordinate ( (rect.left() / ITEMSIZE), rect.top() /ITEMSIZE ) );
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
