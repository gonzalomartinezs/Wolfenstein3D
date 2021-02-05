#include "Configuration.h"
#include "Exceptions/ConfigurationException.h"

#define EXCEPTION_MSG "Key '%s' does not exist. Can't get %s from file %s."

Configuration::Configuration(const char* _filename) {
	this->file = YAML::LoadFile(_filename);
	this->filename = _filename;
}

Configuration::Configuration(const Configuration& config, 
							const std::string& key) {
	this->file = config.file[key];
	this->filename = config.filename;
}

bool Configuration::hasKey(const std::string& key) const {
	return this->file[key];
}

std::string Configuration::getString(const std::string& key) const {
	if (this->file[key]) {
		return std::move(this->file[key].as<std::string>());
	}

	throw ConfigurationException(EXCEPTION_MSG,	key.c_str(), "string",
								this->filename.c_str());
}

float Configuration::getFloat(const std::string& key) const {
	if (this->file[key]) {
		return this->file[key].as<float>();
	}

	throw ConfigurationException(EXCEPTION_MSG, key.c_str(), "float",
								this->filename.c_str());
}

int Configuration::getInt(const std::string& key) const {
	if (this->file[key]) {
		return this->file[key].as<int>();
	}

	throw ConfigurationException(EXCEPTION_MSG, key.c_str(), "int",
								this->filename.c_str());
}

void Configuration::initializeMatrix(const long int row,
									const long int col,
									int** map,
									const std::string& key) const {
	if (!this->file[key]){
		throw ConfigurationException(EXCEPTION_MSG, key.c_str(), "matrix",
									this->filename.c_str());
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			map[i][j] = this->file[key][i][j].as<int>();
		}
	}
}

Configuration::~Configuration() {}