#include "GameException.h"

GameException::GameException(std::string &&error) {
    this->error = error;
}

const char *GameException::what() const noexcept {
    return error.c_str();
}

GameException::~GameException() {}
