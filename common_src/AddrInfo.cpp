#include "AddrInfo.h"
#include "Exceptions/ErrorSocket.h"

#include <cstring>

#define SUCCESS 0

AddrInfo::AddrInfo(const char* ip, const char* port, int flag) {
	struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = flag;

	int status = getaddrinfo(ip, port, &hints, &result);

	if (status != SUCCESS) {
		freeaddrinfo(result);
		throw ErrorSocket("Error initializing socket.");
	}
}

struct addrinfo* AddrInfo::getResult() const {
	return this->result;
}

AddrInfo::~AddrInfo() {
	freeaddrinfo(result);
}