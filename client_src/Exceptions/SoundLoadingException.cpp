#include "SoundLoadingException.h"

SoundLoadingException::SoundLoadingException(const std::string &error) {
    this->msg_error = error;
}

const char *SoundLoadingException::what() const noexcept {
    return msg_error.c_str();
}

