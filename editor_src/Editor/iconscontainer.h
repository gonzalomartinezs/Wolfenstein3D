#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <unordered_map>
#include <QPixmap>

#define MAX_ITEMS 11

class IconsContainer {

public:
    IconsContainer();
    const QPixmap& getIcon(int id);
private:
    std::unordered_map<int,QPixmap> icons;
};

#endif // ICONSCONTAINER_H
