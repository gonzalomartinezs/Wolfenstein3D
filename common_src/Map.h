#ifndef MAP_H
#define MAP_H

#include <cstddef>

class Map {
private:
	long int n_row, n_col;
	int** map;
public:
	Map(const char* file_name);
	int get(int x, int y) const;
	~Map();
private:
	bool outOfRange(int x, int y) const;
};

#endif
