#include "ThClient.h"
#include <thread>

//TESTING
#include <chrono>
#include <string>

#define SECONDS 1
static const std::string STD_MSG = "Dis is a random meSSage XD\n";
//TESTING

#define EMPTY ""

ThClient::ThClient(Peer& _peer) : is_connected(true),
					peer(std::move(_peer)) {}

void ThClient::recvFrom() {
	char buffer[SIZE_BUFFER] = EMPTY;
	int read = 0;

	do {
		read = peer.recv(buffer, SIZE_BUFFER);
		fwrite(buffer, 1, read, stdout);
	} while (read > 0);
}

void ThClient::sendTo() {
	int len_std_msg = STD_MSG.length();

	while (is_connected) {
		peer.send(STD_MSG.c_str(), len_std_msg);
		std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
	}
}

void ThClient::run() {
	std::thread recv_thread(&ThClient::recvFrom, this);
	sendTo();

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