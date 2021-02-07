#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "mapelement.h"
#include "coordinate.h"

class Map
{
public:
    Map();
private:
    std::unordered_map <Coordinate, MapElement> matrix;
};

#endif // MAP_H
