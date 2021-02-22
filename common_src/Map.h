#ifndef MAP_H
#define MAP_H

#include <cstddef>
#include <utility>
#include <vector>
#include "Configuration.h"

class Map {
private:
	long int n_row, n_col;
	int** map;
public:
	explicit Map(const Configuration& config);
    explicit Map(const std::vector<std::vector<int>>& initial_map);
    Map(Map& other) = delete;
    Map& operator=(const Map& other) = delete;

    // Obtiene el valor en la posición x, y de map
	int get(int x, int y) const;

    // Devuelve el valor de n_row y n_col respectivamente
    long int get_n_row() const;
    long int get_n_col() const;

    // Modifica una celda del mapa
    void set(int x, int y, int value);

	~Map();
private:
    // Devuelve true si está fuera del rango, falso encaso contrario
	bool outOfRange(int x, int y) const;
};

#endif
