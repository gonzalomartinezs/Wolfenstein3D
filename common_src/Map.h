#ifndef MAP_H
#define MAP_H

#include <cstddef>

class Map {
private:
	size_t n_row;
	size_t n_col;
	int** map;
public:
	Map(const char* file_name);
	int get(int x, int y) const;
	~Map();
};

#endif
