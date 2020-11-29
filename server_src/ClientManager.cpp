#include "ClientManager.h"
#include "ThClient.h"
#include "../common_src/ErrorSocket.h"

#include <vector>

ClientManager::ClientManager(const char* port) :
							socket(NULL, port, AI_PASSIVE),
							is_connected(true) {
	socket.bind();
}

static void cleanClients(std::vector<ThClient*>& clients) {
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

static void stopClients(const std::vector<ThClient*>& clients) {
	for (auto client : clients) {
		client->stop();
		client->join();
		delete client;
	}
}

void ClientManager::operator()() {
	std::vector<ThClient*> clients;

	socket.listen();

	while (is_connected) {
		try {
			Peer peer = socket.acceptClient();

			clients.push_back(new ThClient(peer));
			clients.back()->start();
			cleanClients(clients);
		} catch (const ErrorSocket& e) {
			stopClients(clients);
		}
	}
}

void ClientManager::stop() {
	is_connected = false;
	socket.stop();
}

ClientManager::~ClientManager() {}