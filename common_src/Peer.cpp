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

int Peer::send() const {
	return 0;
}

int Peer::recv() const {
	return 0;
}

Peer::~Peer() {
	if (peer != PEER_CLOSED) {
		shutdown(peer, SHUT_RDWR);
		close(peer);	
	}
}