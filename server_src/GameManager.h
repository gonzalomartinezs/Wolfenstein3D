#ifndef WOLFENSTEIN3D_GAMEMANAGER_H_
#define WOLFENSTEIN3D_GAMEMANAGER_H_

#include "ClientManager.h"
#include "GamesHandler.h"
#include "Game.h"
#include "Lobby.h"
#include "../common_src/Configuration.h"

class GameManager {
private:
	Configuration config;
	ClientManager* client_manager;
	GamesHandler games;

public:
    /* Constructor */
	GameManager(const char* _file_name);

	void operator()();
	void stop();

	/* Destructor */
	~GameManager();
};

#endif  // WOLFENSTEIN3D_GAMEMANAGER_H_
