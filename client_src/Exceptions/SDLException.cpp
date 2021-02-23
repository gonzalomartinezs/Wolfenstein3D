#include "SDLException.h"

SDLException::SDLException(const std::string &error) {
    this->msg_error = error;
}

const char *SDLException::what() const noexcept {
    return msg_error.c_str();
}
