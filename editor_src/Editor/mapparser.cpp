#include "mapparser.h"
#include <mapelement.h>

MapParser::MapParser() {

}

void MapParser::exportMap(const Map& exported, std::string path) {
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map MapParser::loadMap(std::string path) {
    YAML::Node mapFile;
   // mapFile = YAML::LoadFile(path);
    return Map(0 ,0);
}
