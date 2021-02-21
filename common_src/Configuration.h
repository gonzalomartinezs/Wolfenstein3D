#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "yaml-cpp/yaml.h"
#include <string>

class Configuration {
private:
	YAML::Node file;
	std::string filename;
public:
	// Constructor
	explicit Configuration(const char* _filename);
	// Constructor en base a otro Configuration, se crea a partir de una 
	// referencia a una key con mas keys dentro.
	Configuration(const Configuration& config, const std::string& key);

	// Devuelve true si la key existe, false en caso contrario
	bool hasKey(const std::string& key) const;

	// Obtiene el valor de una key como string
	std::string getString(const std::string& key) const;
	// Obtiene el valor de una key como int
	int getInt(const std::string& key) const;
	// Obtiene el valor de una key como float
	float getFloat(const std::string& key) const;

	// Obtiene el nombre del archivo
	std::string getFileName() const;

	// Inicializa una matriz en map de largo row, ancho col y clave key
	void initializeMatrix(const long int row, const long int col, int** map,
						const std::string& key) const;
	
	~Configuration();
};

#endif
