#include "WindowException.h"

WindowException::WindowException(const std::string &error) {
    this->msg_error = error;
}

const char *WindowException::what() const noexcept {
    return this->msg_error.c_str();
}
