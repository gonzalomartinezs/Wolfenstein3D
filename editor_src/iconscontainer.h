#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <map>
#include "iconsPaths.h"

class ItemList;

enum Editor_icon {
    Barrel,
    Blood,
    Bullet,
    Chaingun,
    Crown,
    Cross,
    Cup,
    Door,
    Food,
    Health,
    Jewelry,
    Key,
    Machinegun,
    Pistol,
    Rpg,
    Slider,
    Spawn,
    Wall0,
    Wall1
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
