#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <map>


class ItemList;

class IconsContainer {

public:
    IconsContainer();
    const QPixmap& getIcon(int id)const;
    void loadItemList(ItemList& list) const;
private:
    std::map<int,QPixmap> icons;
    unsigned size;
};

#endif // ICONSCONTAINER_H
