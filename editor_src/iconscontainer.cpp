#include <QResource>
#include <iostream>
#include "iconscontainer.h"
#include "itemList.h"

#define PUERTA "/icons/arc-triomphe.png"
#define CUCHILLO "icons/bowie-knife.png"


IconsContainer::IconsContainer() {
    this->add(Barrel, BARREL_PATH);
    this->add(Blood, BLOOD_PATH);
    this->add(Bullet, BULLET_PATH);
    this->add(Chaingun, CHAINGUN_PATH);
    this->add(Crown, CROWN_PATH);
    this->add(Cup, CUP_PATH);
    this->add(Door, DOOR_PATH);
    this->add(Health, HEALTH_PATH);
    this->add(Jewelry, JEWELRY_PATH);
    this->add(Key,  KEY_PATH);
    this->add(Machinegun, MACHINEGUN_PATH);
    this->add(Pistol, PISTOL_PATH);
    this->add(Rpg, RPG_PATH);
    this->add(Slider, SLIDER_PATH);
    this->add(Spawn, SPAWN_PATH);
    this->add(Wall0, WALL0_PATH);
}

const QPixmap& IconsContainer::getIcon(editor_icons id)const {
    return this->icons.at(id);
}

void IconsContainer::loadItemList( ItemList &list) const {

    for (auto const& x : icons) {
        list.addIcon(x.first, x.second);
    }
}

void IconsContainer::add(const editor_icons& id, const std::string& path) {
    QPixmap newImage;
    newImage.load( path.c_str() );
    icons.insert ( std::pair<editor_icons,QPixmap>(id,newImage.scaled(this->size, this->size)) );
}

