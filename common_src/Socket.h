#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

#include "Peer.h"

class Socket {
private:
	struct addrinfo* result;
	int file_descriptor;
public:
	Socket(const char* ip, const char* port, int flag);
	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;
	Socket(Socket&& other) = delete;
	Socket& operator=(Socket&& other) = delete;
	Peer connect();
	void bind();
	void listen();
	Peer acceptClient();
	void stop();
	~Socket() noexcept;
};

#endif
