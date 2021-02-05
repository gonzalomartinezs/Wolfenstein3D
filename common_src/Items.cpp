#include "Items.h"
#include "Treasure.h"
#include "HealthRecover.h"
#include "Blood.h"

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
#define KEY_AMMO "ammo"

static const std::vector<std::string> keys = {KEY_CROSS, KEY_CUP, KEY_CHEST,
											KEY_CROWN, KEY_FOOD,
											KEY_MEDICAL_KIT, KEY_BLOOD,
											KEY_ITEM_KEY, KEY_AMMO};

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
	} else if (key == KEY_AMMO) {
		item = new Ammo(config_map.getFloat(KEY_POS_X),
						config_map.getFloat(KEY_POS_Y),
						static_cast<TextureID>(config.getInt(KEY_TEXTURE)),
						config.getInt(KEY_VALUE),
						config.getFloat(KEY_RADIUS));
	}*/
	else {
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

Items::~Items() {
	for (size_t i = 0; i < this->items.size(); ++i) {
		delete this->items[i];
	}
}