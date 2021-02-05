#include "map.h"
#include "mainwindow.h"
#include "itemList.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

Map::Map(std::vector<Item>& items, QWidget *parent) : QWidget(parent), items(items)
{
    Q_INIT_RESOURCE(editor);
    setAcceptDrops(true);
    //ver esto
    setMinimumSize(500, 500);
    setMaximumSize(500, 500); //carguemos 5x5 de vacios.
}

void Map::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::yellow);

    if (focused.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(focused.adjusted(0, 0, -1, -1));
    }

    for (const auto &i : elements){
        painter.drawPixmap(i.rect, i.pixmap);
    }
}

void Map::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(ItemList::editorMimeType()))
        event->accept();
    else
        event->ignore();
}

void Map::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = this->focused;
    this->focused = QRect();
    update(updateRect);
    event->accept();
}


void Map::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = focused.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat(ItemList::editorMimeType())
        && findPiece(targetSquare(event->pos())) == -1) {

        this->focused = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        this->focused = QRect();
        event->ignore();
    }

    update(updateRect);
}

void Map::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(ItemList::editorMimeType())
        && findPiece(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data(ItemList::editorMimeType());
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        MapElement element;
        element.rect = targetSquare(event->pos());
        dataStream >> element.pixmap >> element.id;
        // intentar hacerlo sin mandar el pixmap del otro lado.

        elements.append(element);

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



void Map::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
     int found = findPiece(square);

    if (found == -1)
        return;

    MapElement element = elements.takeAt(found);

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << element.pixmap << element.id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(ItemList::editorMimeType(), itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(element.pixmap);

    if (drag->exec(Qt::MoveAction) != Qt::MoveAction) {
        elements.insert(found, element);
        update(targetSquare(event->pos()));

        /*if (piece.location == square.topLeft() / pieceSize())
            inPlace++;*/
    }
}

const QRect Map::targetSquare(const QPoint &position) const
{
    return QRect(position / ITEMSIZE * ITEMSIZE,
                 QSize(ITEMSIZE, ITEMSIZE));
}
// CAMBIAR ESTO XD.
int Map::findPiece(const QRect &pieceRect) const
{
    for (int i = 0, size = elements.size(); i < size; ++i) {
        if (elements.at(i).rect == pieceRect)
            return i;
    }
    return -1;
}

Item& Map::findItem(int i){
    return items[i];
}








