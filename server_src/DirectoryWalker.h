#ifndef DIRECTORYWALKER_H
#define DIRECTORYWALKER_H

#include <sys/types.h>
#include <dirent.h>
#include <cstddef>
#include <string>

class DirectoryWalker {
private:
	DIR* dir;
public:
	// Recibe el nombre de una carpeta para abrir
	explicit DirectoryWalker(const std::string& folder_name);
	// Devuelve el siguiente archivo
	struct dirent* read();
	
	~DirectoryWalker();
};

#endif
