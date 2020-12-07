#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <atomic>

#include "../common_src/Socket.h"

class ClientManager {
private:
	Socket socket;
	std::atomic<bool> is_connected;
public:
	ClientManager(const char* port);
//	void cleanClients(std::vector<ThClient*>& clients);
	void stopClients(const std::vector<ThClient*>& clients);
	void operator()(std::vector<ThClient*>& clients);
	void stop();
	~ClientManager();
};

#endif
