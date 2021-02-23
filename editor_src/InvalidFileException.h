//
// Created by riedel on 19/2/21.
//

#ifndef EDITOR_INVALIDFILEEXCEPTION_H
#define EDITOR_INVALIDFILEEXCEPTION_H

#include <exception>
#include <string>

  //Exception arrojada cuando se carga un archivo no valido.
class InvalidFileException: std::exception {
 public:
    InvalidFileException(const std::string& error);
    const char* what() const noexcept;
    ~InvalidFileException(){}
private:
    std::string msg_error;
};


#endif //EDITOR_INVALIDFILEEXCEPTION_H
