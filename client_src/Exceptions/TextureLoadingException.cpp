#include "TextureLoadingException.h"

TextureLoadingException::TextureLoadingException(const std::string &error) {
    this->msg_error = error;
}

const char *TextureLoadingException::what() const noexcept {
    return msg_error.c_str();
}
