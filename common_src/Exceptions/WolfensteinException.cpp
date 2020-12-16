#include "WolfensteinException.h"

WolfensteinException::WolfensteinException(std::string &&error) {
    this->error = error;
}

const char *WolfensteinException::what() const noexcept {
    return error.c_str();
}

WolfensteinException::~WolfensteinException() {}
