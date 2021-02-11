#include "mapparser.h"
#include <mapelement.h>
#include <iostream>

MapParser::MapParser() {

}

void MapParser::exportMap(const Map& exported, std::string path) {
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map MapParser::loadMap(std::string path){
    printf("hola jorge");
    std::cout << "hola jorge en c++" << std::cout;
    return Map(0 ,0);
}
