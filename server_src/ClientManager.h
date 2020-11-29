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
	void operator()();
	void stop();
	~ClientManager();
};

#endif
