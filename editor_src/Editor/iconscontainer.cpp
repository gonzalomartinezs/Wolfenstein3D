#include "iconscontainer.h"
#include <QResource>

IconsContainer::IconsContainer(unsigned in_size) {
    //Q_INIT_RESOURCE(editor);
    QResource::registerResource("editor.rcc");
    this->size = in_size;

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
