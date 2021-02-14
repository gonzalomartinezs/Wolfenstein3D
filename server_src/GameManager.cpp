#include "GameManager.h"
#include "../common_src/Exceptions/ConfigurationException.h"

GameManager::GameManager(const char* _file_name) : config(_file_name) {
	this->client_manager = new ClientManager(config);
}

void GameManager::operator()() {
    (*client_manager)(this->games);
}

void GameManager::stop() {
    this->client_manager->stop();
    this->games.finishGames();
}

GameManager::~GameManager() {
	delete client_manager;
}
