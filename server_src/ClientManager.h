#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <atomic>
#include <vector>

#include "ThClient.h"
#include "../common_src/Socket.h"
#include "../common_src/Configuration.h"

class ClientManager {
private:
	Socket socket;
	std::atomic<bool> is_connected;
	const size_t max_clients;
public:
	ClientManager(const Configuration& config);
	void stopClients(const std::vector<ThClient*>& clients);
	void operator()(std::vector<ThClient*>& clients);
	void stop();
	~ClientManager();
};

#endif
