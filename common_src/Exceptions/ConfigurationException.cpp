#include "ConfigurationException.h"
#include <cstdio>
#include <cstdarg>

ConfigurationException::ConfigurationException(const char* format, ...)
												noexcept {
	va_list args;
	va_start(args, format);
	vsnprintf(msg_error, MAX_MSG_ERROR, format, args);
	va_end(args);
}

const char* ConfigurationException::what() const noexcept {
	return msg_error;
}

ConfigurationException::~ConfigurationException() {}
