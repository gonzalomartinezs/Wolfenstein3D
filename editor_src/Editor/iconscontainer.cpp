#include "iconscontainer.h"

IconsContainer::IconsContainer(unsigned in_size) {
    Q_INIT_RESOURCE(editor);

    this->size = in_size;

    unsigned i = 0;
    bool done = false;
    while( !done ) {
       QPixmap newImage;
       if( newImage.load( QStringLiteral(":/img/%1").arg(i) ) ){
            this->icons.insert({i, newImage.scaled(this->size, this->size)});
       } else {
           done = true;
       }
    }
}

const QPixmap& IconsContainer::getIcon(int id){
    return this->icons.at(id);
}
