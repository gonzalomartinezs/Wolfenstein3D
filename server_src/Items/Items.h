#ifndef ITEMS_H
#define ITEMS_H

#include <vector>
#include <string>

#include "Item.h"
#include "../../common_src/Configuration.h"
#include "../Weapons/Rocket.h"

class Items {
private:
	std::vector<Item*> items;

public:
	Items(const Configuration& config, const Configuration& config_map,
		std::vector<Rocket>& rockets);
	Items(Items& other) = delete;
	Items& operator=(const Items& other) = delete;
	Items(Items&& other) = delete;
	Items&& operator=(Item&& other) = delete;

	// Devuelve un puntero al item de la posición i
	Item* operator[](std::size_t i);
	// Devuelve la cantidad de items
	size_t size() const;
	// Carga en msg la información de los items
	void loadItemsInfo(uint8_t* msg, uint32_t& currentByte);
	// Elimina un item del vector
	void remove(size_t i);
	// Agrega un item al vector
	void push_back(Item* item);

	~Items();

private:
	void initialize(const Configuration& config,
					const Configuration& config_map, const std::string& key,
					std::vector<Rocket>& rockets);
};

#endif
