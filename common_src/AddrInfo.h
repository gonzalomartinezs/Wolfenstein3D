#ifndef ADDRINFO_H
#define ADDRINFO_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class AddrInfo {
private:
	struct addrinfo* result;
public:
	AddrInfo(const char* ip, const char* port, int flag);
	struct addrinfo* getResult() const;
	~AddrInfo();
};

#endif
