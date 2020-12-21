#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <string>

class Configuration {
private:
	YAML::Node file;
public:
	Configuration(const char* filename);
	std::string getString(const std::string& key) const;
	int getInt(const std::string& key) const;
	void initializeMatrix(const long int row, const long int col, int** map,
						const std::string& key) const;
	~Configuration();
};

#endif
