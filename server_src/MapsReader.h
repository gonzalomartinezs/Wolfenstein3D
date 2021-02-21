#ifndef MAPSREADER_H
#define MAPSREADER_H

#include <vector>
#include <string>
#include "../common_src/Configuration.h"

#define MAPS_FOLDER_PATH "../server_src/Maps/"

class MapsReader {
private:
	std::vector<Configuration> files;
public:
	// Crea un MapsReader que lee los archivos de mapas de la carpeta
	// que se pasa por parámetro. Los archivos deben ser .yaml/.yml
	explicit MapsReader(const std::string& folder_name);
	// Devuelve el nombre del archivo en la posición i
	std::string getFileName(uint8_t i) const;
	// Devuelve la cantidad de archivos que hay
	size_t size() const;
	// Devuelve el nombre del mapa del archivo de la posición i
	std::string getName(uint8_t i) const;
	// Devuelve la cantidad máxima de jugadores que pueden estar en el mapa i
	int getMaxPlayers(uint8_t i) const;

	~MapsReader();
};

#endif
