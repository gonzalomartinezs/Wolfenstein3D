#include <QResource>
#include "iconscontainer.h"
#include "itemList.h"

#define PUERTA "/icons/arc-triomphe.png"
#define CUCHILLO "icons/bowie-knife.png"


IconsContainer::IconsContainer() {
/*
    while( !done ) {
       QPixmap newImage;
       if( newImage.load( QStringLiteral(":/img/%1").arg(i) ) ){
            this->icons.push_back(newImage.scaled(this->size, this->size));
           i++;
       } else {
           done = true;
       }
    }


QPixmap newImage;
     newImage.load( "../icons/bowie-knife.png" );
    this->icons.push_back(newImage.scaled(this->size, this->size));
    */
}

const QPixmap& IconsContainer::getIcon(int id)const {
    return this->icons.at(id);
}

void IconsContainer::loadItemList( ItemList &list) const {

    for (auto const& x : icons) {
        list.addIcon(x.first, x.second);
    }

}

