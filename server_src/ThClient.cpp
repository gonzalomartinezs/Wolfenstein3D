#include "ThClient.h"
#include <thread>
#include <iostream>
#include <utility>
#include <string>

#define EMPTY ""

ThClient::ThClient(Peer& _peer) : is_connected(true),
                                  peer(std::move(_peer)) {}

void ThClient::recv() {
    uint8_t buffer; //buffer[SIZE_BUFFER]
    int read = 0;

    do {
        read = peer.recv(&buffer, SIZE_BUFFER);
        RecvQueue.push(buffer); //for (i = 0; i < read) push(buffer[i])
    } while (read > 0 && is_connected);
}

void ThClient::send() {
    std::string str;

    try {
        int sent = 0;
        while (is_connected && sent >= 0 && !SendQueue.isWorking()) {
            str = SendQueue.pop();
            int bytesToSend = str.size();
            const uint8_t* buffer = reinterpret_cast<const uint8_t *>(
                                                            str.c_str());
            sent = peer.send(buffer, bytesToSend);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in the send method of"
                        " one of the clients! :(\n" << std::endl;
    }
}

void ThClient::push(uint8_t *buffer, int bytes_to_send) {
    std::string str = std::string(reinterpret_cast<const char*>(buffer),
                                    static_cast<size_t>(bytes_to_send));
    this->SendQueue.push(str);
}

uint8_t ThClient::pop() {
    return RecvQueue.pop();
}

bool ThClient::isEmpty() const {
    return this->RecvQueue.isEmpty();
}

void ThClient::run() {
    std::thread recv_thread(&ThClient::recv, this);
    std::thread send_thread(&ThClient::send, this);

    send_thread.join();
    recv_thread.join();
}

void ThClient::stop() {
    is_connected = false;
    this->SendQueue.doneAdding();
    peer.stop();
    peer.close();
}

bool ThClient::finished() {
    return !is_connected;
}

void ThClient::setName(std::string name) {
    this->name = name;
}

std::string ThClient::getName() const {
    return name;
}

ThClient::~ThClient() {}
