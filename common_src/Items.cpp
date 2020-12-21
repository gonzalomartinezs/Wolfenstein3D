#include "Items.h"

Items::Items(const char* file_name) {
//	YAML::Node file = YAML::LoadFile(file_name);
//	initialize items
/*	TODO:
	if (file["treasure"]) {
		for (cant treasures) this->items.push_back(new Treasure(file["treasure"][i]));
	}
	if (file["food"]) {
		for (cant food) this->items.push_back(new Food(file["food"][i]));
	}
	if (file[...]) {
		for (...) ...
	}
	.
	.
	.
*/
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