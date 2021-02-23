#ifndef MAPHANDLER_H
#define MAPHANDLER_H

#include <QWidget>
#include  <QVector>
#include "map.h"
#include "iconscontainer.h"

class MapHandler : public QWidget {
    Q_OBJECT

 public:
    // Constructor, recibe una referencia IconContainer previamente cargada.
    MapHandler(const IconsContainer& container,const std::string& name = "NoName",
                        unsigned x = 5, unsigned y= 5 , QWidget *parent = nullptr);
    // Cambia el tam del mapa contenido.
    void resizeMap( int x, int y, std::string name = "NoName");
    // Devuelve una referencia constante al mapa contenido.
    const Map& getMap();
    // Carga en el mapa contenido los elementos de la lista.
    void loadElements(std::list<MapElement>& in);

 protected:
    // Interaccion con el usuario mediante Qt.
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    // Calcula a que rectangulo corresponde una posicion de mouse dada.
    const QRect targetSquare(const QPoint &position) const;
    // Calcula a que coodenada corresponde una posicion de mouse dada.
    const Coordinate targetCoordinate(const QPoint& position) const;
    Map map;
    QRect focused;
    const IconsContainer& icons;
};

#endif // MAPHANDLER_H
