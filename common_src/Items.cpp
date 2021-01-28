#include "Items.h"
#include "Treasure.h"
#include "HealthRecover.h"
#include "Blood.h"

Items::Items(Configuration& config) {
	config.addKey("items");

	size_t cant_treasures = config.getInt("cant_treasures");

	for (size_t i = 0; i < cant_treasures; ++i) {
		std::string treasure_number = "treasure_" + std::to_string(i);
		config.addKey(treasure_number);
		this->items.push_back(new Treasure(config.getFloat("pos_x"),
							config.getFloat("pos_y"),
							static_cast<TextureID>(config.getInt("texture")),
							config.getInt("value"),
							config.getFloat("radius")));
		config.removeLastKey();
	}

	size_t cant_food = config.getInt("cant_food");

	for (size_t i = 0; i < cant_food; ++i) {
		std::string food_number = "food_" + std::to_string(i);
		config.addKey(food_number);
		this->items.push_back(new HealthRecover(config.getFloat("pos_x"),
							config.getFloat("pos_y"),
							static_cast<TextureID>(config.getInt("texture")),
							config.getInt("value"),
							config.getFloat("radius")));
		config.removeLastKey();
	}

	size_t cant_medical_kit = config.getInt("cant_medical_kit");

	for (size_t i = 0; i < cant_medical_kit; ++i) {
		std::string medical_kit_number = "medical_kit_" + std::to_string(i);
		config.addKey(medical_kit_number);
		this->items.push_back(new HealthRecover(config.getFloat("pos_x"),
							config.getFloat("pos_y"),
							static_cast<TextureID>(config.getInt("texture")),
							config.getInt("value"),
							config.getFloat("radius")));
		config.removeLastKey();
	}

	size_t cant_blood = config.getInt("cant_blood");

	for (size_t i = 0; i < cant_blood; ++i) {
		std::string blood_number = "blood_" + std::to_string(i);
		config.addKey(blood_number);
		this->items.push_back(new Blood(config.getFloat("pos_x"),
							config.getFloat("pos_y"),
							static_cast<TextureID>(config.getInt("texture")),
							config.getInt("value"),
							config.getFloat("radius")));
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