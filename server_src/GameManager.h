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
	explicit GameManager(const char* _file_name);
	GameManager(GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;

	void operator()();
	void stop();

	/* Destructor */
	~GameManager();
};

#endif  // WOLFENSTEIN3D_GAMEMANAGER_H_
