#include "mapparser.h"
#include <mapelement.h>
#include <yaml-cpp/yaml.h>
#include "iconscontainer.h"

MapParser::MapParser() {
}

void MapParser::exportMap(const Map& exported, std::string path) {
    YAML::Node file;
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map MapParser::loadMap(std::string path) {
   // YAML::Node mapFile;
   // mapFile = YAML::LoadFile(path);
    return Map(0 ,0);
}
