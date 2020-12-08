#ifndef ERRORMAP_H
#define ERRORMAP_H

#include <exception>
#include <string>

class ErrorMap : public std::exception {
private:
	std::string msg_error;
public:
	ErrorMap(const std::string& error);
	const char* what() const noexcept;
	~ErrorMap();
	
};

#endif
