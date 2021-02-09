#include "WeaponItemException.h"

WeaponItemException::WeaponItemException(const std::string& error) {
	this->msg_error = error;
}

const char* WeaponItemException::what() const noexcept {
    return msg_error.c_str();
}

WeaponItemException::~WeaponItemException() {}