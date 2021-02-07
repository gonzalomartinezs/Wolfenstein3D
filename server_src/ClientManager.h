#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <atomic>
#include <vector>

#include "ThClient.h"
#include "Lobby.h"
#include "../common_src/Socket.h"
#include "../common_src/Configuration.h"

class ClientManager {
private:
    Configuration& config;
	Socket socket;
	std::atomic<bool> is_connected;

public:
    /* Constructor */
	ClientManager(Configuration& config);

	void operator()(std::vector<Lobby*>& games);
	void stop();

	/* Destructor */
	~ClientManager();

private:
    uint8_t _blockingRecv(ThClient* client);
    ThClient* _createClient(Peer& peer) const;
    void _talkWithClient(ThClient* client, std::vector<Lobby*>& games);
    void _deleteFinishedGames(std::vector<Lobby*>& games);
    void _deleteFailedClient(ThClient* client);
    int _loadNewGameMsg(uint8_t* msg, std::vector<Lobby*>& games);
    int _loadJoinGameMsg(uint8_t* msg, std::vector<Lobby*>& games);
};

#endif
