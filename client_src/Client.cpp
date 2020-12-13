#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include "Client.h"

#define FLOAT_SIZE sizeof(float)
#define PLAYER_ATTRIBUTES 6
#define MAX_MESSAGE_SIZE 256

ssize_t Client::send(const uint8_t *message, int length) {
    return this->peer.send(message, length);
}

ssize_t Client::sendInstruction(const uint8_t instruction) {
    return send(&instruction, 1);
}

ssize_t Client::receiveCoordenates(DirectedPositionable &player, PlayerView &view,
                                   std::vector<DirectedPositionable> &players) {
    uint8_t received_uints[FLOAT_SIZE];
    uint8_t bytes_to_receive;
    uint8_t bytes_received[MAX_MESSAGE_SIZE];
    memset(bytes_received, 0, MAX_MESSAGE_SIZE);

    this->peer.recv(&bytes_to_receive, 1);
    this->peer.recv(bytes_received, bytes_to_receive);

    if(bytes_to_receive >= FLOAT_SIZE*PLAYER_ATTRIBUTES){
        std::vector<float> coordinates;
        for (std::size_t i = 0; i < FLOAT_SIZE*PLAYER_ATTRIBUTES; i++) {
            received_uints[i%FLOAT_SIZE] = bytes_received[i];
            if((i%FLOAT_SIZE)==(FLOAT_SIZE-1)){
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
void Client::_assignPlayerCoordenates(DirectedPositionable &player, PlayerView &view,
                                      const std::vector<float> &coordenates) {

    player.setX(coordenates[0]);
    player.setY(coordenates[1]);
    player.setDirX(coordenates[2]);
    player.setDirY(coordenates[3]);
    view.movePlaneX(coordenates[4]);
    view.movePlaneY(coordenates[5]);
}

// Asigna las coordenadas recibidasa los demas jugadores del mapa.
void Client::_assignOtherPlayersCoordenates(std::vector<DirectedPositionable>
                                            &players, const std::vector<float>
                                            &coordenates) {

    for(std::size_t j=PLAYER_ATTRIBUTES; j < coordenates.size(); j+=4){
        DirectedPositionable other_player(coordenates[j],
                                          coordenates[j + 1],
                                          coordenates[j+2],
                                          coordenates[j+3], None);
        players.push_back(other_player);
    }
}



