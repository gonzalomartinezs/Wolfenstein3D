//
// Created by riedel on 19/2/21.
//

#include "InvalidFileException.h"

InvalidFileException::InvalidFileException(const std::string &error) {
    std::string msg_error = error;
}

const char* InvalidFileException::what() const noexcept {
    return msg_error.c_str();
}
