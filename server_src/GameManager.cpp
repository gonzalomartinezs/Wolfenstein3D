#include "GameManager.h"
#include "../common_src/Exceptions/ConfigurationException.h"

GameManager::GameManager(const char* _file_name) : config(_file_name) {
	client_manager = new ClientManager(config);
}

void GameManager::operator()() {
    (*client_manager)(this->games);
}

void GameManager::stop() {
    this->client_manager->stop();

    for (auto game : games) {
        game->stop();
        game->join();
        delete game;
    }
}

GameManager::~GameManager() {
	delete client_manager;
}