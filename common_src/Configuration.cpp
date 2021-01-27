#include "Configuration.h"
#include "Exceptions/ConfigurationException.h"

Configuration::Configuration(const char* filename) {
	this->file = YAML::LoadFile(filename);
}

void Configuration::addKey(const std::string& key) {
	if (!this->file[key]) {
		throw ConfigurationException("Key '%s' does not exist.", key.c_str());
	}

	this->main_keys.push_back(key);
}

void Configuration::removeLastKey() {
	this->main_keys.pop_back();
}

std::string Configuration::getString(const std::string& key) const {
	if (this->file[key]) {
		return std::move(this->file[key].as<std::string>());
	}

	throw ConfigurationException("Key '%s' does not exist. Can't get string.",
								key.c_str());
}

float Configuration::_getFloat(const YAML::Node& sub_file, 
							const std::string& key, size_t i) const {
	if (main_keys.size() == i) {
		if (sub_file[key]) {
			return sub_file[key].as<float>();
		}

		throw ConfigurationException("Key '%s' does not exist."
		 							"Can't get float.", key.c_str());
	}

	return _getFloat(sub_file[main_keys[i]], key, i+1);
}

int Configuration::_getInt(const YAML::Node& sub_file, 
							const std::string& key, size_t i) const {
	if (main_keys.size() == i) {
		if (sub_file[key]) {
			return sub_file[key].as<int>();
		}

		throw ConfigurationException("Key '%s' does not exist."
		 							"Can't get int.", key.c_str());
	}

	return _getInt(sub_file[main_keys[i]], key, i+1);
}

float Configuration::getFloat(const std::string& key) const {
	return Configuration::_getFloat(this->file, key, 0);
}

int Configuration::getInt(const std::string& key) const {
	return Configuration::_getInt(this->file, key, 0);
}

void Configuration::initializeMatrix(const long int row,
									const long int col,
									int** map,
									const std::string& key) const {
	if (!this->file[key]){
		throw ConfigurationException("Key '%s' does not exist."
									" Can't initialize matrix.", key.c_str());
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			map[i][j] = this->file[key][i][j].as<int>();
		}
	}
}

Configuration::~Configuration() {}