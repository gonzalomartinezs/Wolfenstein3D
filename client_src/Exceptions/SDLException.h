#ifndef FONTLOADINGEXCEPTION_H
#define FONTLOADINGEXCEPTION_H

#include <exception>
#include <string>

class SDLException: public std::exception {
private:
    std::string msg_error;
public:
    explicit SDLException(const std::string& error);
    const char* what() const noexcept;
    ~SDLException(){}
};


#endif //FONTLOADINGEXCEPTION_H
