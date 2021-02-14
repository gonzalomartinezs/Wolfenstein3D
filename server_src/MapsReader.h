#ifndef MAPSREADER_H
#define MAPSREADER_H

#include <vector>
#include "../common_src/Configuration.h"

#define MAPS_FOLDER_PATH "../server_src/Maps/"

class MapsReader {
private:
	std::vector<Configuration> files;
public:
	explicit MapsReader(const std::string& folder_name);
	std::string getFileName(uint8_t i) const;
	size_t size() const;
	std::string getName(uint8_t i) const;
	int getMaxPlayers(uint8_t i) const;
	~MapsReader();
};

#endif
