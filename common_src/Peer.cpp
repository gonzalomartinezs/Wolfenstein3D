#include "Peer.h"
#include "ErrorSocket.h"

#include <utility>

#define ERROR -1

#define SOCKET_CLOSED 0
#define PEER_CLOSED -1

Peer::Peer(const int _peer) {
	if (_peer == PEER_CLOSED) throw ErrorSocket("Can't connect peer.");

	peer = _peer;
}

Peer::Peer(Peer&& other) {
	peer = std::move(other.peer);
	other.peer = PEER_CLOSED;
}

Peer& Peer::operator=(Peer&& other) {
	peer = std::move(other.peer);
	other.peer = PEER_CLOSED;

	return *this;
}

Peer& Peer::operator=(int other) {
	peer = other;

	return *this;
}

int Peer::send(const uint8_t* buffer, int bytes_to_send) const {
	int total_bytes_sent = 0;
	bool is_open = true;

	while (total_bytes_sent < bytes_to_send && is_open) {
		int bytes_sent = ::send(peer, &buffer[total_bytes_sent],
							bytes_to_send - total_bytes_sent, MSG_NOSIGNAL);

		if (bytes_sent == ERROR || bytes_sent == SOCKET_CLOSED) {
			is_open = false;
		} else {
			total_bytes_sent += bytes_sent;
		}
	}

	return total_bytes_sent;
}

int Peer::recv(uint8_t* buffer, int bytes_to_recv) const {
	int total_bytes_recv = 0;
	bool is_open = true;

	while (total_bytes_recv < bytes_to_recv && is_open) {
		int bytes_received = ::recv(peer, &buffer[total_bytes_recv],
							bytes_to_recv - total_bytes_recv, MSG_NOSIGNAL);

		if (bytes_received == ERROR || bytes_received == SOCKET_CLOSED) {
			is_open = false;
		} else {
			total_bytes_recv += bytes_received;
		}
	}

	return total_bytes_recv;
}

void Peer::stop() {
	if (peer != PEER_CLOSED) shutdown(peer, SHUT_RDWR);
}

void Peer::close() {
	if (peer != PEER_CLOSED) {
		::close(peer);
		peer = PEER_CLOSED;
	}
}

Peer::~Peer() {
	Peer::stop();
	Peer::close();
}