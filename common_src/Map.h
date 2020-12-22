#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include "Configuration.h"

class Map {
private:
	long int n_row, n_col;
	int** map;
public:
	Map(const Configuration& config);
	int get(int x, int y) const;
    long int get_n_row();
    long int get_n_col();
	~Map();
private:
	bool outOfRange(int x, int y) const;
};

#endif
