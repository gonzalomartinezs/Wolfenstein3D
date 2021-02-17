#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <map>
#include "iconsPaths.h"

class ItemList;

class IconsContainer {

public:
    IconsContainer();
    const QPixmap& getIcon(editor_icons)const;
    void loadItemList(ItemList& list) const;
private:
    void add(const editor_icons& id, const std::string& path);
    std::map<editor_icons,QPixmap> icons;
};

#endif // ICONSCONTAINER_H
