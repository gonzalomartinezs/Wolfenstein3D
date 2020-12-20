#ifndef HEALTHRECOVEREXCEPTION_H
#define HEALTHRECOVEREXCEPTION_H

#include <exception>
#include <string>

class HealthRecoverException : public std::exception {
private:
    std::string error;
public:
	HealthRecoverException(std::string&& error);
	const char* what() const noexcept;
	~HealthRecoverException();
};

#endif
