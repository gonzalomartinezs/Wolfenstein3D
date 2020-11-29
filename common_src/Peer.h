#ifndef PEER_H
#define PEER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

class Peer {
private:
	int peer;
public:
	explicit Peer(const int _peer);
	Peer(const Peer& other) = delete;
	Peer& operator=(const Peer& other) = delete;
	Peer(Peer&& other);
	Peer& operator=(Peer&& other);
	Peer& operator=(int other);
	int send() const;
	int recv() const;
	~Peer();
};

#endif
