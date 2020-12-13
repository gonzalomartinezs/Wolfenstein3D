#include "Items.h"

Items::Items(const char* file_name) {
//	YAML::Node file = YAML::LoadFile(file_name);
//	initialize items
/*	TODO:
	if (file["treasure"]) {
		for (cant treasures) this->items(new Treasure(file["treasure"][i]));
	}
	if (file["food"]) {
		for (cant food) this->items(new Food(file["food"][i]));
	}
	if (file[...]) {
		for (...) ...
	}
	.
	.
	.
*/
}

Item& Items::operator[](std::size_t i) const {
	return this->items[i];
}

size_t Items::size() const {
	return this->items.size();
}

Items::~Items() {}