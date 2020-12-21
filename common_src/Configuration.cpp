#include "Configuration.h"

Configuration::Configuration(const char* filename) {
	this->file = YAML::LoadFile(filename);
}

std::string Configuration::getString(const std::string& key) const {
	if (this->file[key]) {
		return std::move(this->file[key].as<std::string>());
	}

	throw "No key found"; //Cambiar por Exception
}

int Configuration::getInt(const std::string& key) const {
	if (this->file[key]) {
		return this->file[key].as<int>();
	}

	throw "No key found"; //Cambiar por Exception	
}

void Configuration::initializeMatrix(const long int row,
									const long int col,
									int** map,
									const std::string& key) const {
	if (!this->file[key]){
		throw "No map key"; //Cambiar por Exception
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			map[i][j] = this->file[key][i][j].as<int>();
		}
	}
}

Configuration::~Configuration() {}