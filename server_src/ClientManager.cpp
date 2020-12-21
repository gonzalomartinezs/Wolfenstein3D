#include "ClientManager.h"
#include "ThClient.h"

#include <vector>

#define KEY_MAX_CLIENTS "max_clients"
#define KEY_PORT "port"

ClientManager::ClientManager(const Configuration& config) :
			socket(NULL, config.getString(KEY_PORT).c_str(), AI_PASSIVE),
			is_connected(true), max_clients(config.getInt(KEY_MAX_CLIENTS)) {
	socket.bind();
}

void ClientManager::stopClients(const std::vector<ThClient*>& clients) {
	for (auto client : clients) {
		client->stop();
		client->join();
		delete client;
	}
}

void ClientManager::operator()(std::vector<ThClient*>& clients) {
	socket.listen();

	while (is_connected && clients.size() < this->max_clients) {
		Peer peer = socket.acceptClient();

		clients.push_back(new ThClient(peer));
		clients.back()->start();
	}
}

void ClientManager::stop() {
	is_connected = false;
	socket.stop();
}

ClientManager::~ClientManager() {}