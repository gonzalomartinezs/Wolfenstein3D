#include <mapelement.h>
#include <yaml-cpp/yaml.h>
#include "mapparser.h"
#include "iconscontainer.h"
#include "coordinate.h"
#include "InvalidFileException.h"

#include <QRect>
#include "mainwindow.h"

#define INVALID_FORMAT "Invalid file format, please use .Yaml"

#define WALL0 1
#define DOOR 2
#define SLIDER 5





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
        hasKey("items");
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
    loadMatrix();
    loadPlayers();
    loadItems();
}

void MapParser::loadItems() {
     YAML::Node items = this->mapFile["items"];
     
    for(YAML::const_iterator it=items.begin(); it!=items.end(); ++it) {
        loadItem(it->second, it->first.as<std::string>() );
    }
}

void MapParser::loadItem (const YAML::Node& item, const std::string& keyName ) {
    Editor_icon id = getID(keyName);
    int n = item.begin()->second.as<int>();
    int _x = 0, _y = 0;
    for (int i = 0; i < n; i++) {
       const YAML::Node& nodePos = item[keyName+"_"+std::to_string(i)];
        int posX = (int) nodePos["pos_x"].as<float>();
        int posY = (int) nodePos["pos_y"].as<float>();
        this->elements.emplace_back(MapElement(id, calculateRect(posX, posY) ));
    }
}

void MapParser::loadPlayers(){
    int n =mapFile["max_players"].as<int>();

    for (int i = 0; i < n ; i++) {
        std::string aux = "player_" + std::to_string(i);
        YAML::Node player = this->mapFile[aux];
        int posX = (int) player["pos_x"].as<float>();
        int posY = (int) player["pos_y"].as<float>();
        this->elements.emplace_back(MapElement(Spawn, calculateRect(posX, posY) ));
    }
}

QRect MapParser::calculateRect(int _x, int _y ) {
    return QRect(QPoint(_x*ITEMSIZE, _y*ITEMSIZE),
                 QSize(ITEMSIZE, ITEMSIZE));
}

void MapParser::loadMatrix() {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            int element = this->mapFile["map"][i][j].as<int>();
            switch (element) {
                case DOOR :
                    elements.emplace_back(MapElement(Door, calculateRect(j, i)));
                    break;
                case WALL0 :
                    elements.emplace_back(MapElement(Wall0, calculateRect(j, i)));
                    break;
                case SLIDER:
                    elements.emplace_back(MapElement(Slider, calculateRect(j, i)));
                    break;
            }
        }
    }
}

Editor_icon MapParser::getID(const std::string &key) {
    if (key == "barrel") return Barrel;
    if (key == "cross") return Cross;
    if (key =="chest") return Jewelry;
    if (key =="crown") return Crown;
    if (key == "cup") return Cup;
    if (key =="food" ) return Food;
    if (key == "medical_kit") return Health;
    if (key =="blood" ) return Blood;
    if (key =="key" ) return Key;
    if (key == "bullet" ) return Bullet;
    if (key == "machine_gun") return Machinegun ;
    if (key == "chain_gun") return Chaingun;
    if (key == "rocket_launcher") return Rpg;
    return Wall1; // default ??
};


