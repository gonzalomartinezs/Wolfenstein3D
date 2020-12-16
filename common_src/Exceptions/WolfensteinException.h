#ifndef WOLFENSTEIN3D_WOLFENSTEINEXCEPTION_H
#define WOLFENSTEIN3D_WOLFENSTEINEXCEPTION_H

#include <exception>
#include <string>

class WolfensteinException : public std::exception {
private:
    std::string error;

public:
    explicit WolfensteinException(std::string&& error);
    const char* what() const noexcept;
    ~WolfensteinException();
};

#endif  // WOLFENSTEIN3D_WOLFENSTEINEXCEPTION_H
