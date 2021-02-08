#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <QWidget>
#include  <QVector>
#include "map.h"

class MapHandler : public QWidget
{
    Q_OBJECT
public:
    explicit MapHandler(unsigned x = 5, unsigned y= 5, QWidget *parent = nullptr);

signals:

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:

    Map map;
    int findPiece(const QRect &pieceRect) const;
    const QRect targetSquare(const QPoint &position) const;
    QRect focused;
};

#endif // MAPHANDLER_H
