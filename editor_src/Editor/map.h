#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "mapelement.h"
#include "coordinate.h"

class Map
{
public:
    Map(const unsigned& x, const unsigned& y);
    void add(const Coordinate& coor, const MapElement& map);
    void remove(const Coordinate& coor);
    bool inRange(const Coordinate& coor)const;
    bool isEmpty(const Coordinate& coor)const;
    unsigned getX() const;
    unsigned getY() const;
    MapElement& get(const Coordinate& coor)const;
private:
    const unsigned x;
    const unsigned y;
    std::unordered_map <std::string, MapElement> matrix;
};

#endif // MAP_H
