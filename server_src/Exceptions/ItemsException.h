#ifndef ITEMSEXCEPTION_H
#define ITEMSEXCEPTION_H

#include <exception>

#define MAX_MSG_ERROR 250

class ItemsException : public std::exception {
private:
	char msg_error[MAX_MSG_ERROR];
public:
	ItemsException(const char* format, ...) noexcept;
	virtual const char* what() const noexcept;
	virtual ~ItemsException();
};

#endif
