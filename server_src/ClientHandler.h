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
    ClientHandler(ThClient* newClient, GamesHandler& games,
                    Configuration& config);

    /* Se encarga de la comunicacion con el cliente en el tiempo que comprende
     * desde que se conecta al server hasta que finaliza el proceso de seleccion
     * de partida/mapa */
    void run() override;

    /* Aborta el proceso de seleccion de partida/mapa */
    void stop() override;

    /* Devuelve true */
    bool finished() override;

    /* Destructor */
    ~ClientHandler();

private:
    /* Intercambia mensajes con el cliente que lo llevan a elegir si
     * desea crear una partida o unirse a una ya existente */
    void _talkWithClient();

    /* Carga en el mensaje la informacion sobre los mapas disponibles en
     * el server */
    int _loadNewGameMsg(uint8_t* msg, const MapsReader& maps_reader);

    /* Carga en el mensaje la informacion sobre las partidas esperando
     * a ser comenzadas */
    int _loadJoinGameMsg(uint8_t* msg);

    /* Recibe el nombre del jugador */
    void _receiveName();

    /* Si se llega a dar el caso de que falla el proceso de seleccion de
     * mapa/partida o se cierra el server en el medio del proceso se termina
     * llamando a este metodo que cierra la conexion y libera los recursos
     * correspondientes */
    void _deleteFailedClient();

    /* Actua como un pop bloqueante sobre la cola del Receive,
     * (Cuyo pop no es bloqueante) */
    uint8_t _blockingRecv();
};

#endif //WOLFENSTEIN3D_CLIENTHANDLER_H_
