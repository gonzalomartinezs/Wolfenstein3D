#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <string>

class Configuration {
private:
	YAML::Node file;
	std::string filename;
public:
	/*Constructor en base a archivo.*/
	Configuration(const char* _filename);
	/*Constructor en base a otro Configuration, se crea a partir de una 
	referencia a una key con mas keys dentro.*/
	Configuration(const Configuration& config, const std::string& key);

	std::string getString(const std::string& key) const;
	int getInt(const std::string& key) const;
	float getFloat(const std::string& key) const;
	void initializeMatrix(const long int row, const long int col, int** map,
						const std::string& key) const;
	~Configuration();
};

#endif
