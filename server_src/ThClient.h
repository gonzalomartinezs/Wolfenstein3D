#ifndef THCLIENT_H
#define THCLIENT_H

#include <atomic>

#include "../common_src/Thread.h"
#include "../common_src/Peer.h"

class ThClient : public Thread {
	std::atomic<bool> is_connected;
	Peer peer;
public:
	ThClient(Peer& _peer);
	void run() override;
	void stop() override;
	bool finished() override;
	~ThClient();
private:
	void recvFrom();
	void sendTo();
};

#endif