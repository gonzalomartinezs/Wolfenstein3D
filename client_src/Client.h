#ifndef CLIENT_H
#define CLIENT_H
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <atomic>
#include "PlayerView.h"
#include "UI_Info.h"
#include "../common_src/Map.h"
#include "../common_src/Peer.h"
#include "../common_src/Socket.h"
#include "../common_src/BlockingQueue.h"
#include "../common_src/ProtectedQueue.h"
#include "../common_src/DirectedPositionable.h"
#include "GameInterface.h"
#include "clientWindow/StringList.h"

class Client {
private:
    Socket socket;
    Peer peer;
    BlockingQueue<int>& instructions;
    ProtectedQueue<UI_Info>& drawing_info;
    std::atomic<bool> playing;

public:
    // Crea un cliente listo para ser utilizado
    Client(const std::string &host, const std::string &service,
           BlockingQueue<int>& instructions,
           ProtectedQueue<UI_Info>& drawing_info);

    // Se borran el constructor por copia y el operador =.
    Client(const Client&) = delete;
    Client operator=(const Client&) = delete;

    std::vector<std::vector<int>> receiveMap();

    // Envia al servidor la proxima instruccion contenida en 'instructions',
    // hasta que surja un error o se corte la conexion.
    void sendInstruction();

    // Recibe informacion del servidor y la escribe en el archivo 'file'.
    ssize_t receiveInformation();

    // Retorna un booleano indicando si el jugador se encuentra jugando o no.
    bool isPlaying() const;

    // Carga el leaderboard con los resultados del juego.
    void loadLeaderboard(GameInterface& interface);

    // Detiene el intercambio de datos entre el cliente y el servidor para
    // la ejecucion del juego.
    void stopInGameInteraction();

    // Realiza un shutdown del cliente y marca la cola bloqueante.
    void shutdown();

    // Libera los recursos utilizados por el cliente.
    ~Client();

private:
    static void _assignPlayerInfo(std::vector<int> &info, uint8_t *bytes_received,
                           bool &important, int &already_parsed);
    static void _assignPlayerState(bool& not_playing, uint8_t *bytes_received, int &already_parsed);
    static void _assignPlayerCoordenates(DirectedPositionable &player, PlayerView &view,
                             std::vector<float> &coordinates,
                             uint8_t *bytes_received, int &already_parsed);
    static void _assignItemsCoordenates(uint8_t *bytes_received,
                                 std::vector<Positionable> &objects,
                                 std::vector<float> &coordinates,
                                 int &already_parsed);
    static void _assignSounds(uint8_t *bytes_received,
                       std::vector<std::pair<int, float>> &sounds,
                       bool &important,
                       int &already_parsed);
    static void _assignSlidersStates(uint8_t *bytes_received,
                              std::vector<int> &sliders_states,
                              int& already_parsed);
    static void _assignOtherPlayersCoordenates(uint8_t *bytes_received,
                                        uint8_t bytes_to_receive,
                                        std::vector<DirectedPositionable> &players,
                                        std::vector<float> &coordinates,
                                        int &already_parsed);

public:
    void sendName(const std::string &username);

    void sendJoinGameChoice();

    void sendNewGameChoice();

    void getMaps(StringList &_maps);

    void sendMapChoice(uint8_t choice);

    void getGames(StringList &list);

    void sendMatchChoice(uint8_t i);

    void sendPlay();
};


#endif //CLIENT_H
