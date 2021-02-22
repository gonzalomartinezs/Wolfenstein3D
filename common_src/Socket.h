#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>

#include "AddrInfo.h"
#include "Peer.h"

class Socket {
private:
	int file_descriptor;
	int peer;

public:
	Socket(const char* ip, const char* port, int flag, bool is_server);
	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;
	Socket(Socket&& other) = delete;
	Socket& operator=(Socket&& other) = delete;
	int getPeer() const;
	void listen();
	Peer acceptClient();
	void stop();
	~Socket() noexcept;

private:
	void connect(const AddrInfo& result);
	void bind(const AddrInfo& result);
};

#endif
