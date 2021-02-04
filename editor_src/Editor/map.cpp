#include "map.h"
#include "itemList.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

Map::Map(QWidget *parent) : QWidget(parent)
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
/*
    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }
*/
    for (const auto &i : elements){
        painter.drawPixmap(i.rect, i.item.pixmap);
    }
}

void Map::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(ItemList::editorMimeType()))
        event->accept();
    else
        event->ignore();
}





