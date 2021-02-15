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
	explicit DirectoryWalker(const std::string& folder_name);
	struct dirent* read();
	~DirectoryWalker();
};

#endif
