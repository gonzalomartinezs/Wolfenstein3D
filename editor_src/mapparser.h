#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "map.h"
#include "mapelement.h"
#include <string>
#include <yaml-cpp/yaml.h>

class MapParser {

public:
    MapParser();
    void exportMap(const Map& exported, std::string path = "map.yamlg") const;
    Map loadMap(std::string path = "map.yaml");
private:
    YAML::Node mapFile;
    bool hasKey(const std::string& key) const;
    unsigned int x;
    unsigned int y;
    std::string name;
    std::list<MapElement> elements;

    void loadSize();

    void loadName();

    void loadElements();
};

#endif // MAPPARSER_H
