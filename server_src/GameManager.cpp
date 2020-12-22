#include "GameManager.h"
#include "../common_src/Exceptions/ConfigurationException.h"
#include "Game.h"

#include <string>

#define KEY_PORT "port"

GameManager::GameManager(const char* _file_name) : config(_file_name) {
	this->game = NULL;
	client_manager = new ClientManager(config);
}

void GameManager::operator()() {
	std::vector<ThClient*> clients;
	try {
		(*client_manager)(clients);

        this->game = new Game(clients, this->config);

        this->game->execute();

	} catch (const std::exception& e) {
		printf("%s", e.what());
	}

	client_manager->stopClients(clients);
}

void GameManager::stop() {
	(*client_manager).stop();
    this->game->stop();
}

GameManager::~GameManager() {
	delete client_manager;
	if (this->game != NULL) delete game;
}