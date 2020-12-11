#ifndef WOLFENSTEIN3D_THCLIENT_H
#define WOLFENSTEIN3D_THCLIENT_H

#include <atomic>

#include "../common_src/Thread.h"
#include "../common_src/Peer.h"
#include "ProtectedQueue.h"

class ThClient : public Thread {
private:
    std::atomic<bool> is_connected;
    Peer peer;
    ProtectedQueue<uint8_t> RecvQueue;

public:
    /* Constructor */
    ThClient(Peer& _peer);
    void run() override;
    bool isEmpty() const;
    uint8_t pop();
    void send(uint8_t* buffer, int bytes_to_send);
    void stop() override;
    bool finished() override;
    /* Destructor */
    ~ThClient();

private:
    void recv();

};

#endif  // WOLFENSTEIN3D_THCLIENT_H