#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "map.h"
#include <string>
#include "yaml-cpp/yaml.h"

class MapParser {
public:
    MapParser();
    void exportMap(const Map& exported, std::string path = "map.yml");
    Map loadMap(std::string path = "map.yml");
};

#endif // MAPPARSER_H
