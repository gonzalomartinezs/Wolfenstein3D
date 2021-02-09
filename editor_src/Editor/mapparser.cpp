#include "mapparser.h"
#include <mapelement.h>

MapParser::MapParser() {

}

void exportMap(const Map& exported, std::string path = "map.yml") {
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map loadMap(std::string path = "map.yml"){
    printf("hola jorge");
}
