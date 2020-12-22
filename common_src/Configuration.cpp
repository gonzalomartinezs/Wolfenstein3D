#include "Configuration.h"
#include "Exceptions/ConfigurationException.h"

Configuration::Configuration(const char* filename) {
	this->file = YAML::LoadFile(filename);
}

std::string Configuration::getString(const std::string& key) const {
	if (this->file[key]) {
		return std::move(this->file[key].as<std::string>());
	}

	throw ConfigurationException("Key '%s' does not exist. Can't get string.",
								key.c_str());
}

int Configuration::getInt(const std::string& key) const {
/*	if (this->file[key]) {
		return this->file[key].as<int>();
	}

	throw ConfigurationException("Key '%s' does not exist. Can't get int",
								key.c_str());
								*/
	return Configuration::getInt(this->file, key);
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

float Configuration::getSubFloat(const std::string& main_key,
								const std::string& sub_key) const {
	return Configuration::getFloat(this->file[main_key], sub_key);
}

int Configuration::getSubInt(const std::string& main_key,
							const std::string& sub_key) const {
	return Configuration::getInt(this->file[main_key], sub_key);
}

float Configuration::getFloat(const YAML::Node& sub_file,
							const std::string& key) const {
	if (sub_file[key]) {
		return sub_file[key].as<float>();
	}

	throw ConfigurationException("Key '%s' does not exist. Can't get float.",
								key.c_str());
}

int Configuration::getInt(const YAML::Node& sub_file,
						const std::string& key) const {
	if (sub_file[key]) {
		return sub_file[key].as<int>();
	}

	throw ConfigurationException("Key '%s' does not exist. Can't get int.",
								key.c_str());
}
Configuration::~Configuration() {}