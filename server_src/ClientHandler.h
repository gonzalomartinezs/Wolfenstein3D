#ifndef WOLFENSTEIN3D_CLIENTHANDLER_H_
#define WOLFENSTEIN3D_CLIENTHANDLER_H_

#include "../common_src/Thread.h"
#include "ThClient.h"
#include "MapsReader.h"
#include "Lobby.h"
#include "GamesHandler.h"

class ClientHandler : public Thread {
private:
    bool endTalking;
    GamesHandler& games;
    ThClient* newClient;
    Configuration& config;

public:
    /* Constructor */
    ClientHandler(ThClient* newClient, GamesHandler& games, Configuration& config);

    void run() override;
    void stop() override;
    bool finished() override;

    /* Destructor */
    ~ClientHandler();

private:
    void _talkWithClient();
    int _loadNewGameMsg(uint8_t* msg, const MapsReader& maps_reader);
    int _loadJoinGameMsg(uint8_t* msg);
    void _deleteFailedClient();
    uint8_t _blockingRecv();
};

#endif //WOLFENSTEINCLIENT_CLIENTHANDLER_H_
