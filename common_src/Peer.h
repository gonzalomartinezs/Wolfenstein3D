#ifndef PEER_H
#define PEER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define SIZE_BUFFER 10

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
	int send(const char* buffer, int bytes_to_send) const;
	int recv(char* buffer, int bytes_to_recv) const;
	void stop();
	void close();
	~Peer();
};

#endif
