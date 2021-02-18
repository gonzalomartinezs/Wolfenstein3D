#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "map.h"
#include <string>

class MapParser {
public:
    MapParser();
    void exportMap(const Map& exported, std::string path = "map.yamlg");
    Map loadMap(std::string path = "map.yaml");
};

#endif // MAPPARSER_H
