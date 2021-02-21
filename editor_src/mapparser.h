#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "map.h"
#include "mapelement.h"
#include "iconscontainer.h"
#include <string>
#include <yaml-cpp/yaml.h>
#include <QRect>

class MapParser {

public:
    MapParser();
    void exportMap(const Map& exported, std::string path = "map.yamlg");
    Map loadMap(std::string path = "map.yaml");

private:
    YAML::Node mapFile;
    YAML::Emitter emitter;
    bool hasKey(const std::string& key) const;
    unsigned int x;
    unsigned int y;
    std::string name;
    std::list<MapElement> elements;
    std::list<Editor_icon> used;
    bool hasBeenUsed ( const Editor_icon& in ) const;
    void loadSize();
    void loadName();
    void loadElements();
    void loadPlayers();
    void loadMatrix();
    QRect calculateRect(int x, int y);
    Coordinate calculateCoor(const QRect&) const;
    Editor_icon getID(const std::string& key);
    void loadItems();

    void loadItem(const YAML::Node &item, const std::string& keyName);

    void exportStructures(const Map& exported);
    bool isStructure(const Editor_icon& id)const;

    void exportPlayers(const Map& exported);

    void exportItems(const Map& exported);

    std::string getItemName(Editor_icon in);

    int getRepetitions(Editor_icon in, const Map &exported);

    std::list<MapElement> getItems(Editor_icon in, std::list<MapElement> &list);
};

#endif // MAPPARSER_H
