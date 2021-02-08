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
    MapElement& get(const Coordinate& coor)const;
    std::list<const MapElement&> getElements() const;
private:
    const unsigned x;
    const unsigned y;
    std::unordered_map <std::string, MapElement> matrix;
};

#endif // MAP_H
