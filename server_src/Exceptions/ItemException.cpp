#include "ItemException.h"

ItemException::ItemException(const std::string& error) {
	this->msg_error = error;
}

const char* ItemException::what() const noexcept {
    return msg_error.c_str();
}

ItemException::~ItemException() {}
