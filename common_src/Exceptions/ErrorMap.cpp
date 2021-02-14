#include "ErrorMap.h"

ErrorMap::ErrorMap(const std::string& error) {
	this->msg_error = error;
}

const char* ErrorMap::what() const noexcept {
    return msg_error.c_str();
}

ErrorMap::~ErrorMap() {}
