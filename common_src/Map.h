#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include <utility>
#include "Configuration.h"
#include "SlidingSurface.h"

class Map {
private:
	long int n_row, n_col;
	int** map;
public:
	Map(const Configuration& config);
	int get(int x, int y) const;
    long int get_n_row() const;
    long int get_n_col() const;
    // Modifica una celda del mapa;
    void set(int x, int y, int value);
    // Retorna las puertas y pasadizos en el mapa.
    std::vector<SlidingSurface> getSlidingSurfaces() const;
	~Map();
private:
	bool outOfRange(int x, int y) const;
};

#endif
