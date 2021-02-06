#include "trashbin.h"

#include "mainwindow.h"
#include "itemList.h"
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

TrashBin::TrashBin(QWidget *parent) : QWidget(parent)
{

}


void TrashBin::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(ItemList::editorMimeType()))
        event->accept();
    else
        event->ignore();
}
