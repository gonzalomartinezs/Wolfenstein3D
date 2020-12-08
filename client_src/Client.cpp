#include <cstring>
#include <sstream>
#include <string>
#include "Client.h"

#define FLOAT_SIZE sizeof(float)
#define PLAYER_ATTRIBUTES 6

ssize_t Client::send(const uint8_t *message, int length) {
    return this->peer.send(message, length);
}

ssize_t Client::sendInstruction(const uint8_t instruction) {
    return send(&instruction, 1);
}

ssize_t Client::receiveCoordenates(PlayerPosition &player, PlayerView &view,
                                   std::vector<PlayerPosition> &players) {
    uint8_t received_uints[FLOAT_SIZE];
    uint8_t bytes_to_receive;
    uint8_t* bytes_received;
    this->peer.recv(&bytes_to_receive, 1);
    this->peer.recv(bytes_received, bytes_to_receive);

    if(bytes_to_receive >= FLOAT_SIZE*PLAYER_ATTRIBUTES){
        std::vector<float> coordinates;
        for (int i = 0; i < FLOAT_SIZE*PLAYER_ATTRIBUTES; i++) {
            received_uints[i%FLOAT_SIZE] = bytes_received[i];
            if((i%FLOAT_SIZE)==0 && i>0){
                float received_float = *(float*)(received_uints);
                coordinates.push_back(received_float);
            }
        }
        _assignPlayerCoordenates(player, view, coordinates);
        _assignOtherPlayersCoordenates(players, coordinates);
    } else {
        throw ; // pocos bytes recibidos
    }
    return 0;
}


void Client::shutdown(int mode) {
//    this->socket.shutdown(mode);
}

//-------------------------- Metodos privados --------------------------------//

// Asigna las coordenadas recibidas a los atributos del jugador
void Client::_assignPlayerCoordenates(PlayerPosition &player, PlayerView &view,
                                      const std::vector<float> &coordenates) {

    player.moveHorizontally(coordenates[0]);
    player.moveVertically(coordenates[1]);
    player.setDirX(coordenates[2]);
    player.setDirY(coordenates[3]);
    view.movePlaneX(coordenates[4]);
    view.movePlaneY(coordenates[5]);
}

// Asigna las coordenadas recibidasa los demas jugadores del mapa.
void
Client::_assignOtherPlayersCoordenates(std::vector<PlayerPosition> &players,
                                       const std::vector<float> &coordenates) {
    for(int j=PLAYER_ATTRIBUTES; j < coordenates.size(); j+=4){
        PlayerPosition other_player(coordenates[j], coordenates[j+1],
                                    coordenates[j+2], coordenates[j+3]);
        players.push_back(other_player);
    }
}



