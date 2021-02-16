#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <map>
#include "itemList.h"
#define MAX_ITEMS 12

class IconsContainer {

public:
    IconsContainer();
    const QPixmap& getIcon(int id)const;
    void loadItemList( ItemList& list);
private:
    std::map<int,QPixmap> icons;
    unsigned size;
};

#endif // ICONSCONTAINER_H
