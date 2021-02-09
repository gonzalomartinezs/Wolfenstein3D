#ifndef MAP_H
#define MAP_H

#include <list>
#include <unordered_map>
#include "mapelement.h"


class Coordinate; // una foward declaration para safar.

class Map {
public:
    Map(const unsigned& x, const unsigned& y);
    void add(const Coordinate& coor, const MapElement& map);
    void remove(const Coordinate& coor);
    bool inRange(const Coordinate& coor);
    bool isEmpty(const Coordinate& coor)const;
    unsigned getX() const;
    unsigned getY() const;
    const MapElement& get(const Coordinate& coor)const;
    const MapElement& get(const QPoint& point) const;
    std::list<MapElement> getElements() const;
private:
    const unsigned x;
    const unsigned y;
    std::unordered_map <std::string, MapElement> matrix;
};

#endif // MAP_H
