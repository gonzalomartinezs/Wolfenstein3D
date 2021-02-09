#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <vector>

#define MAX_ITEMS 12

class IconsContainer {

public:
    IconsContainer(unsigned size);
    const QPixmap& getIcon(int id);
    unsigned getSize();
    const std::vector<Qpixmap>& getIcons();
private:
    std::vector<QPixmap> icons;
    unsigned size;

};

#endif // ICONSCONTAINER_H
