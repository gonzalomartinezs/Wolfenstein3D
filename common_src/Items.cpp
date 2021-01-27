#include "Items.h"
#include "Treasure.h"

Items::Items(Configuration& config) {
	config.addKey("items");

	size_t cant_treasures = config.getInt("cant_treasures");

	for (size_t i = 0; i < cant_treasures; ++i) {
		std::string treasure_number = "treasure_" + std::to_string(i);
		config.addKey(treasure_number);
		this->items.push_back(new Treasure(config.getFloat("pos_x"),
							config.getFloat("pos_y"),
							static_cast<TextureID>(config.getInt("texture")),
							config.getInt("value")));
		config.removeLastKey();
	}

	config.removeLastKey();
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