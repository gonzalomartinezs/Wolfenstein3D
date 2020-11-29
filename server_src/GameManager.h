#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "ClientManager.h"

class GameManager {
private:
	ClientManager* client_manager;
public:
	GameManager(const char* file_name);
	void operator()();
	void stop();
	~GameManager();
};

#endif
