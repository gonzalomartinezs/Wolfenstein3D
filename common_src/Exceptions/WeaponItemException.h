#ifndef WEAPONITEMEXCEPTION_H
#define WEAPONITEMEXCEPTION_H

#include <exception>
#include <string>

class WeaponItemException : public std::exception {
private:
	std::string msg_error;
public:
	explicit WeaponItemException(const std::string& error);
	const char* what() const noexcept;
	~WeaponItemException();
};

#endif
