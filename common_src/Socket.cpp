#include "Socket.h"
#include "ErrorSocket.h"

#define SUCCESS 0

#define PEER_ERROR -1
#define FD_ERROR -1
#define MAX_CLIENTS 10

Socket::Socket(const char* ip, const char* port, int flag) :
				file_descriptor(FD_ERROR) {
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

Peer Socket::connect() {
	struct addrinfo* result_aux = result;

	while (result_aux) {
		int peer = socket(result_aux->ai_family, result_aux->ai_socktype,
							result_aux->ai_protocol);

		if (peer != PEER_ERROR) {
			if (::connect(peer, result_aux->ai_addr,
				result_aux->ai_addrlen)	== SUCCESS) {
				return Peer(peer);
			} else {
				close(peer);
			}
		}

		result_aux = result_aux->ai_next;
	}

	throw ErrorSocket("Can't connect to the server.");
}

void Socket::bind() {
	bool is_connected = false;
	struct addrinfo* result_aux = result;

	while (result_aux && !is_connected) {
		file_descriptor = socket(result_aux->ai_family,
								result_aux->ai_socktype, 
								result_aux->ai_protocol);
		int option = 1;
		setsockopt(file_descriptor, SOL_SOCKET, SO_REUSEADDR, &option,
					sizeof(option));

		if (file_descriptor != FD_ERROR) {
			if (::bind(file_descriptor, result_aux->ai_addr,
					result_aux->ai_addrlen) == SUCCESS) {
				is_connected = true;
			} else {
				close(file_descriptor);
			}
		}

		result_aux = result_aux->ai_next;
	}

	if (!is_connected) throw ErrorSocket("Can't bind to the server.");
}

void Socket::listen() {
	::listen(file_descriptor, MAX_CLIENTS);
}

Peer Socket::acceptClient() {
	return Peer(accept(file_descriptor, NULL, NULL));
}

void Socket::stop() {
	if (file_descriptor != FD_ERROR) {
		shutdown(file_descriptor, SHUT_RDWR);
	}
}

Socket::~Socket() noexcept {
	if (file_descriptor != FD_ERROR) {
		shutdown(file_descriptor, SHUT_RDWR);
		close(file_descriptor);
	}

	freeaddrinfo(result);
}
