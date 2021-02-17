#ifndef RAYCASTINGEXCEPTION_H
#define RAYCASTINGEXCEPTION_H

#include <exception>

#define MAX_MSG_ERROR 250

class RaycastingException : public std::exception {
private:
    char msg_error[MAX_MSG_ERROR];
public:
    RaycastingException(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~RaycastingException();
};

#endif //RAYCASTINGEXCEPTION_H
