#include "MapsReader.h"

#include <sys/types.h>
#include <dirent.h>
#include <cstddef>

#define KEY_MAP_NAME "map_name"
#define KEY_MAX_PLAYERS "max_players"

static bool isYAMLFile(const std::string& file_name) {
	size_t file_name_size = file_name.size();

	if (file_name_size < 5) return false;

	return (file_name.compare(file_name_size-4, 4, ".yml") == 0 ||
			file_name.compare(file_name_size-5, 5, ".yaml") == 0);
}

MapsReader::MapsReader(const std::string& folder_name) {
	DIR* dir = opendir(folder_name.c_str());

	if (dir == NULL) throw "Error initializing folder.";

	struct dirent* file;

	while ((file = readdir(dir)) != NULL) {
		std::string file_name = file->d_name;
		if (isYAMLFile(file_name)) {
			file_name = MAPS_FOLDER_PATH + file_name;
			this->files.emplace_back(file_name.c_str());
		}
	}

	closedir(dir);
}

std::string MapsReader::getFileName(uint8_t i) const {
	return this->files[i].getFileName();
}

size_t MapsReader::size() const {
	return this->files.size();
}

std::string MapsReader::getName(uint8_t i) const {
	return this->files[i].getString(KEY_MAP_NAME);
}

int MapsReader::getMaxPlayers(uint8_t i) const {
	return this->files[i].getInt(KEY_MAX_PLAYERS);
}

MapsReader::~MapsReader() {}