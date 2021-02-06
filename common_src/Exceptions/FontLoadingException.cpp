#include "FontLoadingException.h"

FontLoadingException::FontLoadingException(const std::string &error) {
    this->msg_error = error;
}

const char *FontLoadingException::what() const noexcept {
    return msg_error.c_str();
}
