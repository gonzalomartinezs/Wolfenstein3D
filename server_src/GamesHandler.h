#ifndef WOLFENSTEIN3D_GAMESHANDLER_H_
#define WOLFENSTEIN3D_GAMESHANDLER_H_

#include "Game.h"
#include "Lobby.h"

class GamesHandler {
private:
    std::vector<Lobby*> games;
    std::mutex gamesMtx;

public:
    /* Constructor */
    GamesHandler();

    void pushGameAndStart(Lobby* newGame);

    void pushClient(uint8_t gameID, ThClient* newClient);

    void finishGames();

    bool gameInProgress(uint8_t gameID);

    std::string getMapName(uint8_t gameID);

    uint8_t getPlayersAmountInLobby(uint8_t gameID);

    uint8_t getMaxPlayers(uint8_t gameID);

    size_t size();

    /* Destructor */
    ~GamesHandler();
};

#endif //WOLFENSTEIN3D_GAMESHANDLER_H_
