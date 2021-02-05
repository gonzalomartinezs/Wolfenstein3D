#include "GameManager.h"
#include "../common_src/Exceptions/ConfigurationException.h"
#include "Game.h"

#include <string>

GameManager::GameManager(const char* _file_name) : config(_file_name) {
	this->game = NULL;
	client_manager = new ClientManager(config);
}

void GameManager::operator()() {
	std::vector<ThClient*> clients;
	try {
		(*client_manager)(clients);
		Configuration config_map("../common_src/map_1.yaml");

        this->game = new Game(clients, this->config, config_map);

        this->game->execute();

	} catch (const std::exception& e) {
		printf("%s", e.what());
	}

	client_manager->stopClients(clients);
}

void GameManager::stop() {
	(*client_manager).stop();
    if (this->game != NULL) this->game->stop();
}

GameManager::~GameManager() {
	delete client_manager;
	if (this->game != NULL) delete game;
}