#ifndef ITEMS_H
#define ITEMS_H

#include <vector>

#include "Item.h"

class Items {
private:
	std::vector<Item*> items;
public:
	Items(const char* file_name);
	Items(Item& other) = delete;
	Items& operator=(const Items& other) = delete;
	Items(Item&& other) = delete;
	Items&& operator=(Item&& other) = delete;
	Item* operator[](std::size_t i);
	size_t size() const;
	void remove(size_t i);
	~Items();
};

#endif
