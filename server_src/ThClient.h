#ifndef THCLIENT_H
#define THCLIENT_H

#include <atomic>

#include "../common_src/Thread.h"
#include "../common_src/Peer.h"
#include "ProtectedQueue.h"

class ThClient : public Thread {
private:
	std::atomic<bool> is_connected;
	Peer peer;
	ProtectedQueue queue;
public:
	ThClient(Peer& _peer);
	void run() override;
	bool isEmpty() const;
	uint8_t pop();
	void send(uint8_t* buffer, int bytes_to_send);
	void stop() override;
	bool finished() override;
	~ThClient();
private:
	void recv();
	
};

#endif