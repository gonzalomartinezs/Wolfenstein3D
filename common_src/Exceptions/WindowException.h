#ifndef WINDOWEXCEPTION_H
#define WINDOWEXCEPTION_H


#include <exception>
#include <string>

class WindowException: public std::exception {
private:
    std::string msg_error;
public:
    explicit WindowException(const std::string& error);
    const char* what() const noexcept;
    ~WindowException(){};

};

#endif //WINDOWEXCEPTION_H
