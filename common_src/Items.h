#ifndef ITEMS_H
#define ITEMS_H

#include <vector>

#include "Item.h"
#include "Configuration.h"

class Items {
private:
	std::vector<Item*> items;
public:
	Items(const Configuration& config, const Configuration& config_map);
	Items(Items& other) = delete;
	Items& operator=(const Items& other) = delete;
	Items(Items&& other) = delete;
	Items&& operator=(Item&& other) = delete;
	Item* operator[](std::size_t i);
	size_t size() const;
	void loadItemsInfo(uint8_t* msg, uint8_t& currentByte);
	void remove(size_t i);
	~Items();
private:
	void initialize(const Configuration& config,
					const Configuration& config_map, const std::string& key);
};

#endif
