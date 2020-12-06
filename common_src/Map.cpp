#include "Map.h"
#include "yaml-cpp/yaml.h"

#define KEY_MAP "map"
#define KEY_ROW "length"
#define KEY_COL "width"

Map::Map(const char* file_name) : n_row(0), n_col(0) {
	YAML::Node file = YAML::LoadFile(file_name);

	n_row = file[KEY_ROW].as<size_t>();
	n_col = file[KEY_COL].as<size_t>();

	map = new int*[n_row];

	for (std::size_t i = 0; i < n_row; ++i) {
		map[i] = new int[n_col];
	}

	for (std::size_t i = 0; i < n_row; ++i) {
		for (std::size_t j = 0; j < n_col; ++j) {
			map[i][j] = file[KEY_MAP][i][j].as<int>();
		}
	}
}

int Map::get(int x, int y) const {
	return map[x][y];
}

Map::~Map() {
	for (std::size_t i = 0; i < n_row; ++i) {
		delete[] map[i];
	}

	delete[] map;
}