#include "GameManager.h"
#include "yaml-cpp/yaml.h"

#include <string>

#define KEY_PORT "port"

GameManager::GameManager(const char* file_name) {
	YAML::Node file = YAML::LoadFile(file_name);

	if (file[KEY_PORT]) {
		const std::string port = file[KEY_PORT].as<std::string>();
		client_manager = new ClientManager(port.c_str());
	} else {
		throw ErrorYAML("Key '%s' does not exist in %s.", KEY_PORT,
						file_name);
	}
}

void GameManager::operator()() {
	(*client_manager)();
}

void GameManager::stop() {
	(*client_manager).stop();
}

GameManager::~GameManager() {
	delete client_manager;
}