#include "Socket.h"
#include "Exceptions/ErrorSocket.h"

#define SUCCESS 0

#define PEER_ERROR -1
#define FD_ERROR -1
#define MAX_CLIENTS 10

Socket::Socket(const char* ip, const char* port, int flag, bool is_server) :
				file_descriptor(FD_ERROR), peer(PEER_ERROR) {
	AddrInfo result(ip, port, flag);

	if (is_server) Socket::bind(result);
	else Socket::connect(result);
}

void Socket::connect(const AddrInfo& result) {
	bool is_connected = false;
	struct addrinfo* result_tmp = result.getResult();

	while (result_tmp && !is_connected) {
		int _peer = socket(result_tmp->ai_family, result_tmp->ai_socktype,
							result_tmp->ai_protocol);

		if (_peer != PEER_ERROR) {
			if (::connect(_peer, result_tmp->ai_addr,
				result_tmp->ai_addrlen)	== SUCCESS) {
				this->peer = _peer;
				is_connected = true;
			} else {
				close(_peer);
			}
		}

		result_tmp = result_tmp->ai_next;
	}

	if (!is_connected) throw ErrorSocket("Can't connect to the server.");
}

void Socket::bind(const AddrInfo& result) {
	bool is_connected = false;
	struct addrinfo* result_tmp = result.getResult();

	while (result_tmp && !is_connected) {
		file_descriptor = socket(result_tmp->ai_family,
								result_tmp->ai_socktype, 
								result_tmp->ai_protocol);
		int option = 1;
		setsockopt(file_descriptor, SOL_SOCKET, SO_REUSEADDR, &option,
					sizeof(option));

		if (file_descriptor != FD_ERROR) {
			if (::bind(file_descriptor, result_tmp->ai_addr,
					result_tmp->ai_addrlen) == SUCCESS) {
				is_connected = true;
			} else {
				close(file_descriptor);
			}
		}

		result_tmp = result_tmp->ai_next;
	}

	if (!is_connected) throw ErrorSocket("Can't bind to the server.");
}

int Socket::getPeer() const {
	return this->peer;
}

void Socket::listen() {
	::listen(file_descriptor, MAX_CLIENTS);
}

Peer Socket::acceptClient() {
	Peer peer(accept(file_descriptor, NULL, NULL));

	return peer;
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
}
