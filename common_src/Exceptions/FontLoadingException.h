#ifndef FONTLOADINGEXCEPTION_H
#define FONTLOADINGEXCEPTION_H

#include <exception>
#include <string>

class FontLoadingException: public std::exception {
private:
    std::string msg_error;
public:
    explicit FontLoadingException(const std::string& error);
    const char* what() const noexcept;
    ~FontLoadingException(){};

};


#endif //FONTLOADINGEXCEPTION_H
