#ifndef ERRORSOCKET_H
#define ERRORSOCKET_H

#include <exception>
#include <cstring>
#include <cerrno>

#define MAX_MSG_ERROR 200

class ErrorSocket : public std::exception {
private:
	char msg_error[MAX_MSG_ERROR];
public:
	ErrorSocket() noexcept;
	explicit ErrorSocket(const char* msg) noexcept;
	virtual const char* what() const noexcept;
	virtual ~ErrorSocket();
};

#endif
