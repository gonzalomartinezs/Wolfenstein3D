#include "ErrorSocket.h"

ErrorSocket::ErrorSocket() noexcept {
	int _errno = errno;

	memcpy(msg_error, strerror(_errno), strlen(strerror(_errno)) + 1);
}
ErrorSocket::ErrorSocket(const char* msg) noexcept {
	memcpy(msg_error, msg, strlen(msg) + 1);
}

const char* ErrorSocket::what() const noexcept {
	return msg_error;
}

ErrorSocket::~ErrorSocket() {}
