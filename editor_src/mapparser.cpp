#include <mapelement.h>
#include <yaml-cpp/yaml.h>
#include "mapparser.h"
#include "iconscontainer.h"
#include "coordinate.h"
#include "InvalidFileException.h"

#include <QRect>
#include "mainwindow.h"
#include <fstream>

#define INVALID_FORMAT "Invalid file format, please use .Yaml"

#define WALL0 1
#define DOOR 2
#define SLIDER 5





MapParser::MapParser() {
}

void MapParser::exportMap(const Map& exported, std::string path) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "map_name" << YAML::Value << exported.getName();
    emitter << YAML::Key << "max_players" << YAML::Value << exported.getNumberOfPlayers();
    x = exported.getY(); y = exported.getY();
    emitter << YAML::Key << "length" << YAML::Value << y;
    emitter << YAML::Key << "width" << YAML::Value << x;

    exportStructures(exported);
    exportPlayers(exported);
    exportItems(exported);
    emitter << YAML::EndMap;
    std::ofstream out(path);
    out << emitter.c_str();
}

void MapParser::exportStructures(const Map& exported) {
    emitter << YAML::Key << "map";
    std::list<MapElement> list = exported.getElements();
    std::vector<std::vector<int>> matrix;

    for (int i = 0; i <  y; ++i) {
        std::vector<int> v1;
        for (int j = 0; j < x ; ++j) {
            v1.push_back(0);
        }
        matrix.push_back(v1);
}

    for(const auto &i : list) {
        if (isStructure( i.getId() ) ) {
            Coordinate cor = calculateCoor(i.getRect());
            int aux;
            if(i.getId() == Wall0) aux = WALL0;
            if(i.getId() == Wall1) aux = WALL0;
            if(i.getId() == Door)  aux = DOOR;
            if(i.getId() == Slider) aux = SLIDER;
            matrix[cor.getY()][cor.getX()] = aux;
        }
    }
    emitter << YAML::BeginSeq;
    for (const auto &line : matrix ) {
        emitter << YAML::Flow << line;
    }
    emitter << YAML::EndSeq;
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
    for(const auto&i : elements) {
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
}

bool MapParser::isStructure(const Editor_icon &id) const {
    if ( id ==Wall0 || id == Wall1 || id == Slider
           || id == Door) return true;
    return false;
}

Coordinate MapParser::calculateCoor(const QRect &rect) const {
    rect.x();
    rect.y(); //error puede estar aca.
    Coordinate coor( rect.x()/ITEMSIZE, rect.y()/ITEMSIZE);
    return coor;
}

void MapParser::exportPlayers(const Map& exported) {

    std::list<MapElement> list = exported.getElements();

    int number = 0;
    for (const auto& i : list) {
        if(i.getId() == Spawn) {
            int pos_x = i.calculateX();
            int pos_y = i.calculateY();
            std::string aux  = "player_" + std::to_string(number);  number++;
            emitter << YAML::Key << aux;
            emitter << YAML::Value << YAML::BeginMap;
                emitter << YAML::Key << "pos_x" << YAML::Value << pos_x + 0.5;
                emitter << YAML::Key << "pos_y" << YAML::Value << pos_y + 0.5;
                emitter << YAML::Key << "dir_x" << YAML::Value << 1;
                emitter << YAML::Key << "dir_y" << YAML::Value << 0;
            emitter << YAML::EndMap;
        }
    }
}

void MapParser::exportItems(const Map& exported) {
    std::list<MapElement> list = exported.getElements();
    emitter << YAML::Key << "items";
    emitter << YAML::Value << YAML::BeginMap; //1
    for (const auto& i : list) {
        std::string name = getItemName( i.getId() );
        if( name.empty() ) continue;
        if( hasBeenUsed(i.getId() ) ) continue;
        this->used.emplace_back(i.getId());
        emitter << YAML::Key << name;
        emitter << YAML::Value << YAML::BeginMap; //2
        std::list<MapElement> it = getItems(i.getId(), list);
        int n = 0;
        emitter << YAML::Key << "cant_" + name << YAML::Value << it.size();
        for (auto &j : it) {
            emitter << YAML::Key << name + "_" + std::to_string(n);
            emitter << YAML::Value << YAML::BeginMap;
            emitter << YAML::Key << "pos_x" << YAML::Value << j.calculateX() + 0.5;
            emitter << YAML::Key << "pos_y" << YAML::Value << j.calculateY() + 0.5;
            emitter << YAML::EndMap;
            n++;
        }
        emitter << YAML::EndMap; //2
    }
    emitter << YAML::EndMap; //1
};

std::string MapParser::getItemName(Editor_icon in) {

    switch (in) {
        case Blood:
            return "blood";
            break;
        case Bullet:
            return "bullet";
            break;
        case Chaingun:
            return "chain_gun";
            break;
        case Crown:
            return "crown";
            break;
        case Cross:
            return "cross";
            break;
        case Cup:
            return "cup";
            break;
        case Food:
            return "food";
            break;
        case Health:
            return "medical_kit";
            break;
        case Jewelry:
            return "chest";
            break;
        case Key:
            return "key";
            break;
        case Machinegun:
            return "machine_gun";
            break;
        case Rpg:
            return "rocket_launcher";
            break;
        default:
            return std::string();
    }
}

std::list<MapElement> MapParser::getItems(Editor_icon in, std::list<MapElement>& list) {
    std::list<MapElement> r;
    for (auto i : list) {
        if(i.getId() == in) {
            r.emplace_back(i);
        }
    }
    return r;
}

bool MapParser::hasBeenUsed (const Editor_icon& in) const {
    for (auto &i : used) {
        if(i == in) return true;
    }
    return false;
}