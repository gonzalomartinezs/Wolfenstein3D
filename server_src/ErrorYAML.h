#ifndef ERRORYAML_H
#define ERRORYAML_H

#include <exception>

#define MAX_MSG_ERROR 250

class ErrorYAML : public std::exception {
private:
	char msg_error[MAX_MSG_ERROR];
public:
	ErrorYAML(const char* format, ...) noexcept;
	virtual const char* what() const noexcept;
	virtual ~ErrorYAML();
};

#endif
