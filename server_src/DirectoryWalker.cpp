#include "DirectoryWalker.h"
#include "Exceptions/GameException.h"

DirectoryWalker::DirectoryWalker(const std::string& folder_name) {
	this->dir = opendir(folder_name.c_str());

	if (this->dir == NULL) throw GameException("Error initializing folder.");
}

struct dirent* DirectoryWalker::read() {
	return readdir(this->dir);
}

DirectoryWalker::~DirectoryWalker() {
	closedir(this->dir);
}