#ifndef WOLFENSTEIN3D_GAMESHANDLER_H_
#define WOLFENSTEIN3D_GAMESHANDLER_H_

#include <vector>
#include <string>

#include "Game.h"
#include "Lobby.h"

class GamesHandler {
private:
    std::vector<Lobby*> games;
    std::mutex gamesMtx;

public:
    /* Constructor */
    GamesHandler();

    /* Agrega un juego nuevo (thread-safe) */
    void pushGameAndStart(Lobby* newGame);

    /* Agrega un nuevo cliente (Jugador) a la partida con ID
     * igual a gameID (thread-safe) */
    void pushClient(uint8_t gameID, ThClient* newClient);

    /* Detiene la ejecucion de todas las partidas que estan siendo ejecutadas */
    void finishGames();

    /* Devuelve true si la partida con ID igual a gameID esta en curso */
    bool gameInProgress(uint8_t gameID);

    /* Devuelve el nombre del mapa del game con ID igual a gameID */
    std::string getMapName(uint8_t gameID);

    /* Devuelve la cantidad de jugadores conectados a la partida con ID
     * igual a gameID */
    uint8_t getPlayersAmountInLobby(uint8_t gameID);

    /* Devuelve la cantidad maxima de jugadores que admite el mapa de la partida
     * con ID igual a gameID */
    uint8_t getMaxPlayers(uint8_t gameID);

    /* Devuelve la cantidad de partidas en curso */
    size_t size();

    /* Destructor */
    ~GamesHandler();
};

#endif //WOLFENSTEIN3D_GAMESHANDLER_H_
