#ifndef WOLFENSTEIN3D_CLIENTMANAGER_H_
#define WOLFENSTEIN3D_CLIENTMANAGER_H_

#include <atomic>
#include <vector>

#include "ThClient.h"
#include "Lobby.h"
#include "../common_src/Socket.h"
#include "../common_src/Configuration.h"
#include "GamesHandler.h"

class ClientHandler;

class ClientManager {
private:
    Configuration& config;
	Socket socket;
	std::atomic<bool> is_connected;

public:
    /* Constructor */
	explicit ClientManager(Configuration& config);

	void operator()(GamesHandler& games);
	void stop();

	/* Destructor */
	~ClientManager();

private:
    ThClient* _createClient(Peer& peer) const;
    void _deleteFinishedChoosingClients(
    							std::vector<ClientHandler*>& choosingClients);
};

#endif  // WOLFENSTEIN3D_CLIENTMANAGER_H_
