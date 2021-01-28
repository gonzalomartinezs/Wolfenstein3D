#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <string>

class Configuration {
private:
	YAML::Node file;
	std::vector<std::string> main_keys;
public:
	Configuration(const char* filename);
	void addKey(const std::string& key);
	void removeLastKey();
	std::string getString(const std::string& key) const;
	int getInt(const std::string& key) const;
	float getFloat(const std::string& key) const;
	void initializeMatrix(const long int row, const long int col, int** map,
						const std::string& key) const;
	~Configuration();
private:
	bool keyExists(const YAML::Node& sub_file, const std::string& key,
					size_t i) const;
	int _getInt(const YAML::Node& sub_file,	const std::string& key,
				 size_t i) const;
	float _getFloat(const YAML::Node& sub_file,	const std::string& key,
					size_t i) const;
};

#endif
