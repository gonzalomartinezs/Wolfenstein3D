#include "ClientManager.h"
#include "ThClient.h"
#include "ClientHandler.h"

#include <vector>
#include <algorithm>
#include <iostream>

#define KEY_PORT "port"

ClientManager::ClientManager(Configuration& config) : config(config),
                socket(NULL, config.getString(KEY_PORT).c_str(), AI_PASSIVE),
                is_connected(true) {
	socket.bind();
}

void ClientManager::operator()(GamesHandler& games) {
    std::vector<ClientHandler*> choosingClients;

	socket.listen();

	while (this->is_connected) {
        try {
            Peer peer = socket.acceptClient();

            if (this->is_connected) {
                ThClient* newClient = this->_createClient(peer);
                this->_deleteFinishedChoosingClients(choosingClients);
                choosingClients.push_back(new ClientHandler(newClient, games, this->config));
                choosingClients.back()->start();
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
	}

    for (auto client : choosingClients) {
        client->stop();
        client->join();
        delete client;
    }
}

ThClient* ClientManager::_createClient(Peer& peer) const {
    ThClient* newClient = new ThClient(peer);
    newClient->start();
    return newClient;
}

/* Devuelve true si el Thread termino su ejecucion, false en
 * caso contrario */
bool _clientHasFinished(Thread* thread) {
    if (thread->finished() == true) {
        thread->join();
        delete thread;
        return true;
    }
    return false;
}

void ClientManager::_deleteFinishedChoosingClients(std::vector<ClientHandler*>& choosingClients) {
    choosingClients.erase(std::remove_if(choosingClients.begin(), choosingClients.end(), _clientHasFinished), choosingClients.end());
}

void ClientManager::stop() {
    this->is_connected = false;
    this->socket.stop();
}

ClientManager::~ClientManager() {}
