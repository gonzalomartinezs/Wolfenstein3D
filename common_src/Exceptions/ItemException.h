#ifndef ITEMEXCEPTION_H
#define ITEMEXCEPTION_H

#include <exception>
#include <string>

class ItemException : public std::exception {
private:
	std::string msg_error;
public:
	explicit ItemException(const std::string& error);
	const char* what() const noexcept;
	~ItemException();
};

#endif
