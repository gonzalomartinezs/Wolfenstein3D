#include "Items.h"
#include "Treasure.h"
#include "HealthRecover.h"
#include "Blood.h"
#include "MachineGunItem.h"
#include "ChainGunItem.h"
#include "RocketLauncherItem.h"
#include "BulletItem.h"
#include <cstring>

#include "Exceptions/ItemsException.h"

//Treasures
#define KEY_CROSS "cross"
#define KEY_CUP "cup"
#define KEY_CHEST "chest"
#define KEY_CROWN "crown"

//Health recover
#define KEY_FOOD "food"
#define KEY_MEDICAL_KIT "medical_kit"
#define KEY_BLOOD "blood"

//Others
#define KEY_ITEM_KEY "key"
#define KEY_BULLETS "bullet"

//Weapons
#define KEY_MACHINE_GUN "machine_gun"
#define KEY_CHAIN_GUN "chain_gun"
#define KEY_ROCKET_LAUNCHER "rocket_launcher"

static const std::vector<std::string> keys = {KEY_CROSS, KEY_CUP, KEY_CHEST,
											KEY_CROWN, KEY_FOOD,
											KEY_MEDICAL_KIT, KEY_BLOOD,
											KEY_ITEM_KEY, KEY_BULLETS,
											KEY_MACHINE_GUN, KEY_CHAIN_GUN,
											KEY_ROCKET_LAUNCHER};

static Item* initializeItem(const Configuration& config, 
							const Configuration& config_map,
							const std::string& key) {
	Item* item;

	if (key == KEY_CROSS || key == KEY_CUP || key == KEY_CHEST ||
		key == KEY_CROWN) {
		item = new Treasure(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else if (key == KEY_FOOD || key == KEY_MEDICAL_KIT) {
		item = new HealthRecover(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else if (key == KEY_BLOOD) {
		item = new Blood(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	}/* else if (key == KEY_ITEM_KEY) {
		item = new Key(config_map.getFloat(KEY_POS_X),
						config_map.getFloat(KEY_POS_Y),
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS));
	}*/ else if (key == KEY_BULLETS) {
		item = new BulletItem(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else if (key == KEY_MACHINE_GUN) {
		item = new MachineGunItem(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else if (key == KEY_CHAIN_GUN) {
		item = new ChainGunItem(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else if (key == KEY_ROCKET_LAUNCHER) {
		item = new RocketLauncherItem(config, config_map.getFloat(KEY_POS_X),
							config_map.getFloat(KEY_POS_Y));
	} else {
		throw ItemsException("Key '%s' is not a valid item key.",
							key.c_str());
	}

	return item;
}

void Items::initialize(const Configuration& config,
						const Configuration& config_map,
						const std::string& key) {
	std::string item_cant = "cant_" + key;

	size_t n = config_map.getInt(item_cant);

	for (size_t i = 0; i < n; ++i) {
		std::string item_number = key + "_" + std::to_string(i);
		Configuration config_item(config_map, item_number);
		this->items.push_back(initializeItem(config, config_item, key));
	}
}

Items::Items(const Configuration& config, const Configuration& config_map) {
	for (size_t i = 0; i < keys.size(); ++i) {
		if (config_map.hasKey(keys[i])) {
			Configuration sub_config(config, keys[i]);
			Configuration sub_config_map(config_map, keys[i]);

			Items::initialize(sub_config, sub_config_map, keys[i]);
		}
	}
}

Item* Items::operator[](std::size_t i) {
	return this->items[i];
}

size_t Items::size() const {
	return this->items.size();
}

void Items::remove(size_t i) {
//	if (Items::size() < i || Items::size() == 0) throw "Element out of range";
	delete this->items[i];
	this->items.erase(this->items.begin() + i);
}

void Items::loadItemsInfo(uint8_t* msg, uint8_t &currentByte) {
    float aux;
    uint8_t id, size;

    size = static_cast<uint8_t>(this->items.size());
    memcpy(msg + currentByte, &size, sizeof(uint8_t));
    currentByte += sizeof(uint8_t);

    for (size_t i = 0; i < this->items.size(); i++) {
        aux = this->items[i]->getX();
        memcpy(msg + currentByte, &aux, sizeof(float));
        currentByte += sizeof(float);

        aux = this->items[i]->getY();
        memcpy(msg + currentByte, &aux, sizeof(float));
        currentByte += sizeof(float);

        id = this->items[i]->getTexture();
        memcpy(msg + currentByte, &id, sizeof(uint8_t));
        currentByte += sizeof(uint8_t);
    }
}

Items::~Items() {
	for (size_t i = 0; i < this->items.size(); ++i) {
		delete this->items[i];
	}
}