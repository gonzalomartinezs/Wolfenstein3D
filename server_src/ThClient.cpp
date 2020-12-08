#include "ThClient.h"
#include <thread>

#define EMPTY ""

ThClient::ThClient(Peer& _peer) : is_connected(true),
					peer(std::move(_peer)) {}

void ThClient::recv() {
	uint8_t buffer; //buffer[SIZE_BUFFER]
	int read = 0;

	do {
		read = peer.recv(&buffer, SIZE_BUFFER);
		queue.push(buffer); //for (i = 0; i < read) push(buffer[i])
	} while (read > 0 && is_connected);
}

void ThClient::send(uint8_t* buffer, int bytes_to_send) {
	peer.send(buffer, bytes_to_send);
}

uint8_t ThClient::pop() {
	return queue.pop();
}

bool ThClient::isEmpty() const {
	return this->queue.isEmpty();
}

void ThClient::run() {
	std::thread recv_thread(&ThClient::recv, this);

	recv_thread.join();
}

void ThClient::stop() {
	is_connected = false;
	peer.stop();
	peer.close();
}

bool ThClient::finished() {
	return !is_connected;
}

ThClient::~ThClient() {}