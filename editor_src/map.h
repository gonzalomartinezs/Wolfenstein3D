#ifndef MAP_H
#define MAP_H

#include <list>
#include <unordered_map>
#include "mapelement.h"
#include "iconscontainer.h"


class Coordinate; // una foward declaration para safar.

class Map {
public:
    Map(const unsigned& x = 5, const unsigned& y = 5);
    void add(const Coordinate& coor, const MapElement& map);
    void remove(const Coordinate& coor);
    bool inRange(const Coordinate& coor)const;
    bool isEmpty(const Coordinate& coor)const;
    unsigned getX() const;
    unsigned getY() const;
    unsigned getNumberOfPlayers()const;
    const MapElement& get(const Coordinate& coor)const;
    const MapElement& get(const QPoint& point) const;
    std::list<MapElement> getElements() const;
    const std::string& getName() const;
    void setName(const std::string& name);
    void setOutline();

    void resizeMap(int x, int y);

private:
     unsigned x;
     unsigned y;
    std::string name;
    std::unordered_map <std::string, MapElement> matrix;
};

#endif // MAP_H
