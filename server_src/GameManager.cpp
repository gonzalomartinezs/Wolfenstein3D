#include "GameManager.h"
#include "yaml-cpp/yaml.h"
#include "ErrorYAML.h"
#include "Game.h"

#include <string>

#define KEY_PORT "port"

GameManager::GameManager(const char* file_name) {
//	YAML::Node file = YAML::LoadFile(file_name);
//
//	if (file[KEY_PORT]) {
//		const std::string port = file[KEY_PORT].as<std::string>();
		client_manager = new ClientManager("8080");
//	} else {
//		throw ErrorYAML("Key '%s' does not exist in %s.", KEY_PORT,
//						file_name);
//	}
}

void GameManager::operator()() {
	std::vector<ThClient*> clients;
	try {
		(*client_manager)(clients);

		Game game(clients);

		game.execute();
	} catch (const std::exception& e) {
		printf("%s", e.what());
	}
	
	client_manager->stopClients(clients);
}

void GameManager::stop() {
	(*client_manager).stop();
}

GameManager::~GameManager() {
	delete client_manager;
}