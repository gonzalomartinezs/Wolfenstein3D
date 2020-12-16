#ifndef WOLFENSTEIN3D_THCLIENT_H
#define WOLFENSTEIN3D_THCLIENT_H

#include <atomic>
#include "../common_src/Thread.h"
#include "../common_src/Peer.h"
#include "../common_src/ProtectedQueue.h"
#include "../common_src/BlockingQueue.h"

class ThClient : public Thread {
private:
    std::atomic<bool> is_connected;
    Peer peer;
    ProtectedQueue<uint8_t> RecvQueue;
    BlockingQueue<std::string> SendQueue;

public:
    /* Constructor */
    ThClient(Peer& _peer);

    void run() override;
    bool isEmpty() const;
    uint8_t pop();
    void push(uint8_t* buffer, int bytes_to_send);
    void stop() override;
    bool finished() override;

    /* Destructor */
    ~ThClient();

private:
    void recv();
    void send();

};

#endif  // WOLFENSTEIN3D_THCLIENT_H