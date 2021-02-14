#include "iconscontainer.h"
#include <QResource>


#define PUERTA "/icons/arc-triomphe.png"
#define CUCHILLO "icons/bowie-knife.png"

/*
<file alias="2">icons/brick-wall.png</file>
<file alias="3">icons/flying-shuriken.png</file>
<file alias="4">icons/heart-tower.png</file>
<file alias="5">icons/luger.png</file>
<file alias="6">icons/player-base.png</file>
<file alias="7">icons/revolver.png</file>
<file alias="8">icons/steyr-aug.png</file>
<file alias="9">icons/stick-grenade.png</file>
<file alias="10">icons/tesla-turret.png</file>
<file alias="11">icons/uzi.png</file>
*/

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
     newImage.load( PUERTA );
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
