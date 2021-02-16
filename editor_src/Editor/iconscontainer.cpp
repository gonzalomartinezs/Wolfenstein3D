#include "iconscontainer.h"
#include <QResource>


#define PUERTA "/icons/arc-triomphe.png"
#define CUCHILLO "icons/bowie-knife.png"



IconsContainer::IconsContainer(unsigned in_size) {
    QResource::registerResource("editor.rcc");
    this->size = in_size;
    /*
    unsigned i = 0;
    bool done = false;
    while( !done ) {
       QPixmap newImage;
       if( newImage.load( QStringLiteral(":/img/%1").arg(i) ) ){
            this->icons.push_back(newImage.scaled(this->size, this->size));
           i++;
       } else {
           done = true;
       }
    }
    */
    QPixmap newImage;
     newImage.load( "../icons/bowie-knife.png" );
    this->icons.push_back(newImage.scaled(this->size, this->size));
}

const QPixmap& IconsContainer::getIcon(int id)const {
    return this->icons.at(id);
}

unsigned IconsContainer::getSize()const {
    return this->size;
}

const std::vector<QPixmap>& IconsContainer::getIcons()const {
    return icons;
}
