#include "HealthRecoverException.h"

HealthRecoverException::HealthRecoverException(std::string&& error) {
	this->error = error;
}
const char* HealthRecoverException::what() const noexcept {
	return error.c_str();
}

HealthRecoverException::~HealthRecoverException() {}