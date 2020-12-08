#ifndef WOLFENSTEIN3D_GAMEEXCEPTION_H
#define WOLFENSTEIN3D_GAMEEXCEPTION_H

#include <exception>
#include <string>

class GameException : public std::exception {
private:
    std::string error;

public:
    explicit GameException(std::string&& error);
    const char* what() const noexcept;
    ~GameException();
};

#endif //WOLFENSTEIN3D_GAMEEXCEPTION_H
