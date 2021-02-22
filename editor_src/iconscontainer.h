#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <unordered_map>
#include "iconsPaths.h"

class ItemList;

enum Editor_icon {

    Spawn,
    Wall0,
    Wall1,
    Door,
    Slider,
    LockedDoor,
    Key,

    Chaingun,
    Machinegun,
    Rpg,
    Bullet,

    Food,
    Health,
    Blood,

    Crown,
    Cross,
    Cup,
    Jewelry

};

class IconsContainer {

public:
    IconsContainer(const unsigned& size);
    const QPixmap& getIcon(Editor_icon)const;
    void loadItemList(ItemList& list) const;
private:
    void add(const Editor_icon& id, const std::string& path);
    std::map<Editor_icon,QPixmap> icons;
    const unsigned iconSize;
};

#endif // ICONSCONTAINER_H
