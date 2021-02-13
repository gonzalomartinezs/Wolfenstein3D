#include "mapparser.h"
#include <mapelement.h>
#include "yaml-cpp/yaml.h"

MapParser::MapParser() {

}

void MapParser::exportMap(const Map& exported, std::string path) {
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map MapParser::loadMap(std::string path) {
    printf("hola jorge");
    return Map(0 ,0);
}
