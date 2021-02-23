#ifndef WOLFENSTEIN3D_LOBBY_H_
#define WOLFENSTEIN3D_LOBBY_H_

#include "../common_src/Thread.h"
#include "ThClient.h"
#include "Game.h"
#include <vector>
#include <string>

class Lobby : public Thread {
private:
    std::vector<ThClient*> clients;
    Game* game;
    Configuration& config;
    Configuration config_map;
    std::mutex clientsMtx;

    std::string mapName;
    std::atomic<int> maxPlayers;
    std::atomic<bool> gameInProgress;
    std::atomic<bool> gameIsOver;

public:
    /* Constructor */
    Lobby(ThClient* mainClient, Configuration& config,
        const std::string& map_file_name);

    /* Agrego un nuevo cliente (Jugador) a la partida (thread-safe) */
    void pushClientIfNotInProgress(ThClient* newPlayer);

    /* Devuelve el nombre del mapa */
    std::string getMapName();

    /* Devuelve la cantidad de jugadores conectados a la partida */
    uint8_t getPlayersAmountInLobby();

    /* Devuelve la cantidad maxima de jugadores que admite el mapa de la partida */
    uint8_t getMaxPlayers();

    /* Comprende desde esperar la instruccion para comenzar la partida y ejecutar
     * el juego hasta cerrar la conexion con cada uno de los clientes */
    void run() override;

    /* Termina la ejecucion del juego */
    void stop() override;

    /* Devuelve true si la partida finalizo */
    bool finished() override;

    /* Devuelve true si el juego esta en curso */
    bool inProgress();

    /* Destructor */
    ~Lobby();

private:
    /* Comienza la ejecucion del juego */
    void _startGame();

    /* Cierra la conexion con todos los clientes de la partida y libera
     * los correspondientes recursos */
    void _stopClients();
};


#endif //WOLFENSTEIN3D_LOBBY_H_
