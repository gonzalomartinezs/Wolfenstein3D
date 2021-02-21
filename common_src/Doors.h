#ifndef DOORS_H
#define DOORS_H

#include <vector>
#include "Map.h"
#include "ManualDoor.h"
#include "SlidingSurface.h"

class Doors {
private:
	std::vector<ManualDoor*> doors;

public:
	Doors(const Map& map);
	// Devuelve una referencia del ManualDoor en la posición i
	ManualDoor& operator[](const size_t i);
	// Devuelve la cantidad de puertas
	size_t size() const;

	// Carga en msg la información de las puertas
	void loadDoorsInfo(uint8_t* msg, uint8_t &currentByte);

	~Doors();

private:
	// Calcula la dirección en la que apunta la puerta
	void _calculateDirection(const Map& map, long x, long y,
							int* dir_x, int* dir_y);
};

#endif
