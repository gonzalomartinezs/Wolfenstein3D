#include "ClientManager.h"
#include "ThClient.h"

#include <vector>

#define MAX_CLIENTS 1

ClientManager::ClientManager(const char* port) :
							socket(NULL, port, AI_PASSIVE),
							is_connected(true) {
	socket.bind();
}
/*
void ClientManager::cleanClients(std::vector<ThClient*>& clients) {
	std::size_t len_clients = clients.size();
	std::vector<ThClient*> clients_tmp;

	for (std::size_t i = 0; i < len_clients; ++i) {
		if (clients[i]->finished()) {
			clients[i]->join();
			delete clients[i];
		} else {
			clients_tmp.push_back(clients[i]);
		}
	}

	clients.swap(clients_tmp);
}
*/
void ClientManager::stopClients(const std::vector<ThClient*>& clients) {
	for (auto client : clients) {
		client->stop();
		client->join();
		delete client;
	}
}

void ClientManager::operator()(std::vector<ThClient*>& clients) {
	socket.listen();

	while (is_connected && clients.size() < MAX_CLIENTS) {
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