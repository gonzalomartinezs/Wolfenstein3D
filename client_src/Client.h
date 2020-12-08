#ifndef TP3_TALLER_CLIENT_H
#define TP3_TALLER_CLIENT_H
#include <fstream>
#include "../common_src/Socket.h"
#include "../common_src/Peer.h"
#include "../common_src/PlayerPosition.h"
#include "PlayerView.h"
#include <string>
#include <utility>
#include <vector>

class Client {
private:
    Socket socket;
    Peer peer;
    std::string host;
    std::string service;

public:
    // Crea un cliente listo para ser utilizado
    Client(std::string host, std::string service):
                                socket(host.c_str(), service.c_str(), 0),
                                peer(socket.connect()){}

    // Se borran el constructor por copia y el operador =.
    Client(const Client&) = delete;
    Client operator=(const Client&) = delete;

    // Envia al servidor el mensaje contenido en 'message' al servidor.
    // Retorna la cantidad de bytes enviados.
    ssize_t send(const uint8_t *message, int length);

    // Envía al servidor la instruccion introducida por el usuario.
    // Retorna la cantidad de bytes enviados.
    ssize_t sendInstruction(uint8_t instruction);

    // Recibe informacion del servidor y la escribe en el archivo 'file'.
    ssize_t receiveCoordenates(PlayerPosition &player, PlayerView &view,
                               std::vector<PlayerPosition> &players);

    // Realiza un shut down del cliente de acuerdo al modo recibido.
    // 0 -> SHUT_RD, cierra el socket para lectura.
    // 1 -> SHUT_WR, cierra el socket para escritura.
    // 2 -> SHUT_RDWR, cierra el socket para lectoescritura.
    void shutdown(int mode);

    // Libera los recursos utilizados por el cliente.
    ~Client(){}

private:
    void _assignPlayerCoordenates(PlayerPosition &player, PlayerView &view,
                                  const std::vector<float> &coordenates);
    void
    _assignOtherPlayersCoordenates(std::vector<PlayerPosition> &players,
                                   const std::vector<float> &coordenates);

};


#endif //TP3_TALLER_CLIENT_H
