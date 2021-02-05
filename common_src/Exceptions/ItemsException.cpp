#include "ItemsException.h"
#include <cstdio>
#include <cstdarg>

ItemsException::ItemsException(const char* format, ...)	noexcept {
	va_list args;
	va_start(args, format);
	vsnprintf(msg_error, MAX_MSG_ERROR, format, args);
	va_end(args);
}

const char* ItemsException::what() const noexcept {
	return msg_error;
}

ItemsException::~ItemsException() {}