#ifndef MAP_H
#define MAP_H

#include <list>
#include <unordered_map>

#include "mapelement.h"
#include "coordinate.h"

/* Clase mapa, usada para guardar los elementos que fueron colocados mediante
 * el drag n drop.
 */
class Map {
 public:
    //Constructor, por defecto el tam es (5x5).
    Map(const unsigned& x = 5, const unsigned& y = 5);
    //Agrega elemento al mapa.
    void add(const Coordinate& coor, const MapElement& map);
    // Elimina elemento del mapa.
    void remove(const Coordinate& coor);
    // Responde a la pregunta. IsInRange.
    bool inRange(const Coordinate& coor) const;
    // Responde a la pregunta is empty.
    bool isEmpty(const Coordinate& coor) const;
    // Devuelve componente X.
    unsigned getX() const;
    // Devuelve componente Y.
    unsigned getY() const;
    // Devuelve la cantidad de jugadores que hay en el mapa.
    unsigned getNumberOfPlayers()const;
    // Devuelve una lista con los elementos del mapa.
    const MapElement& get(const Coordinate& coor)const;
    // Devuelve una lista de elementos del mapa.
    std::list<MapElement> getElements() const;
    // Devuelve nombre del mapa.
    const std::string& getName() const;
    // Fija nombre del mapa.
    void setName(const std::string& name);
    // Fija tam del mapa.
    void resizeMap(int x, int y);

 private:
     void setPerimeter();
     void clearPerimeter();
     std::list<Coordinate> calculatePerimeter() const;
     unsigned x;
     unsigned y;
    std::string name;
    std::unordered_map <std::string, MapElement> matrix;
    bool isBorder(const Coordinate &coor) const;
};

#endif // MAP_H
