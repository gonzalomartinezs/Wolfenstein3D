#include "RaycastingException.h"
#include <cstdio>
#include <cstdarg>

RaycastingException::RaycastingException(const char* format, ...)	noexcept {
    va_list args;
    va_start(args, format);
    vsnprintf(msg_error, MAX_MSG_ERROR, format, args);
    va_end(args);
}

const char* RaycastingException::what() const noexcept {
    return msg_error;
}

RaycastingException::~RaycastingException() {}

