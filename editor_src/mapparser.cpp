#include <mapelement.h>
#include <yaml-cpp/yaml.h>
#include "mapparser.h"
#include "iconscontainer.h"
#include "coordinate.h"
#include "InvalidFileException.h"

#define INVALID_FORMAT "Invalid file format, please use .Yaml"

MapParser::MapParser() {
}

void MapParser::exportMap(const Map& exported, std::string path) const{
    YAML::Node file;
    std::list<MapElement> list = exported.getElements();
    for(auto& i : list) {
        printf("%i /", i.id);
    }
}

Map MapParser::loadMap(std::string path) {
    try {
        this->mapFile = YAML::LoadFile(path);
        hasKey("map_name");
    } catch ( ... ){
        throw (InvalidFileException(INVALID_FORMAT));
    }
    this->loadSize();
    this->loadName();
    this->loadElements();
    Map map(this->x,this->y);
    for(const auto&i : elements){
        map.add(Coordinate(i.calculateX(), i.calculateY()) , i);
    }
    map.setName(name);
    return map;
}

bool MapParser::hasKey(const std::string &key) const {
    return (this->mapFile[key]);
}

void MapParser::loadSize() {
    if( !hasKey("length") || !hasKey("width") ) {
        throw InvalidFileException(INVALID_FORMAT);
    }
    x = mapFile["width"].as<int>();
    y = mapFile["length"].as<int>();
}

void MapParser::loadName() {
    if( !hasKey("map_name") ) {
        throw InvalidFileException(INVALID_FORMAT);
    }
    name = mapFile["map_name"].as<std::string>();
}

void MapParser::loadElements() {
    // xd, xd xd xd. la verdadera paja.
}


