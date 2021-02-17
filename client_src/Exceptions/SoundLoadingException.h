#ifndef SOUNDLOADINGEXCEPTION_H
#define SOUNDLOADINGEXCEPTION_H

#include <exception>
#include <string>

class SoundLoadingException: public std::exception {
private:
    std::string msg_error;
public:
    explicit SoundLoadingException(const std::string& error);
    const char* what() const noexcept;
    ~SoundLoadingException(){}
};

#endif //SOUNDLOADINGEXCEPTION_H
