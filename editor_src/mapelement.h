#ifndef MAPELEMENT_H
#define MAPELEMENT_H

#include "iconscontainer.h"
#include "coordinate.h"
#include <QRect>

/*Clase MapElement, representa un elemento Del mapa.
 * Contiene un Id y una coordenada.
*/
class MapElement {
public:
    MapElement();
    MapElement(const Editor_icon& id, const Coordinate& coor);
    //Constructor con QRect, simplifica mucho la interaccion con Qt.
    MapElement(const Editor_icon& id, const QRect& rect);
    //Devuelve el id asociado al elemento.
    const Editor_icon& getId() const;
    //Devuelve la coordenada asociada al elemento.
    const Coordinate& getCoor() const;
    // Calcula Qrect correspondiente al elemento.
    QRect getRect() const;

    //Redefinicion de operadores.
    MapElement(MapElement &in);
    MapElement(MapElement &&in);
    MapElement(const MapElement &in);
    bool operator==( const MapElement& rhs);
    MapElement& operator=(const MapElement& in);
private:
    Editor_icon id;
    Coordinate coor;
};

#endif // MAPELEMENT_H
