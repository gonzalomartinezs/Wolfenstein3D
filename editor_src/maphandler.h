#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <QWidget>
#include  <QVector>

#include "map.h"
#include "iconscontainer.h"
#include "coordinate.h"

class MapHandler : public QWidget {
    Q_OBJECT


public:
    void resizeMap( int x, int y, std::string name = "NoName");

    explicit MapHandler(const IconsContainer& container,const std::string& name = "NoName",
                        unsigned x = 5, unsigned y= 5 , QWidget *parent = nullptr);
    const Map& getMap();
    void loadElements(std::list<MapElement>& in);


signals:
    void showOccupiedPosition ();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    const QRect targetSquare(const QPoint &position) const;
    const Coordinate targetCoordinate(const QPoint& position) const;
    Map map;
    QRect focused;
    const IconsContainer& icons;
};

#endif // MAPHANDLER_H
