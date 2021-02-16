#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <map>

#define MAX_ITEMS 12

class IconsContainer {

public:
    IconsContainer(unsigned size);
    const QPixmap& getIcon(int id)const;
    unsigned getSize()const;
    const std::vector<QPixmap>& getIcons()const;
private:
    std::map<int,QPixmap> icons;
    unsigned size;

};

#endif // ICONSCONTAINER_H
