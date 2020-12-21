#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ClientManager.h"
#include "Game.h"
#include "../common_src/Configuration.h"

class GameManager {
private:
	Configuration config;
	ClientManager* client_manager;
	Game* game;
public:
	GameManager(const char* _file_name);
	void operator()();
	void stop();
	~GameManager();
};

#endif
