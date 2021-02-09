#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <unordered_map>
#include <QPixmap>

#define MAX_ITEMS 12

class IconsContainer {

public:
    IconsContainer(unsigned size);
    const QPixmap& getIcon(int id);
    unsigned getSize();
private:
    std::unordered_map<int,QPixmap> icons;
    unsigned size;
};

#endif // ICONSCONTAINER_H
