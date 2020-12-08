#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ClientManager.h"
#include "Game.h"

class GameManager {
private:
	ClientManager* client_manager;
	const char* file_name;
public:
	GameManager(const char* _file_name);
	void operator()();
	void stop();
	~GameManager();
};

#endif
