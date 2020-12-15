#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include "Client.h"

#define FLOAT_SIZE sizeof(float)
#define PLAYER_ATTRIBUTES 6
#define PLAYERS_ATTRIBUTES 5
#define MAX_MESSAGE_SIZE 256

ssize_t Client::send(const uint8_t *message, int length) {
    return this->peer.send(message, length);
}

ssize_t Client::sendInstruction(const uint8_t instruction) {
    return send(&instruction, 1);
}

ssize_t Client::receiveCoordenates(DirectedPositionable &player, PlayerView &view,
                                   std::vector<DirectedPositionable> &players) {
    uint8_t bytes_to_receive;
    uint8_t bytes_received[MAX_MESSAGE_SIZE];
    memset(bytes_received, 0, MAX_MESSAGE_SIZE);

    this->peer.recv(&bytes_to_receive, 1);
    this->peer.recv(bytes_received, bytes_to_receive);

    int player_size = PLAYER_ATTRIBUTES * FLOAT_SIZE;

    if(bytes_to_receive >= player_size){
        std::vector<float> coordinates;
        _assignPlayerCoordenates(player, view, coordinates, player_size,
                                 bytes_received);
        _assignOtherPlayersCoordenates(bytes_received, bytes_to_receive, players, coordinates);
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
void
Client::_assignPlayerCoordenates(DirectedPositionable &player, PlayerView &view,
                                 std::vector<float> &coordinates,
                                 int player_size, uint8_t *bytes_received) {
    float received;
    for (std::size_t i = 0; i < PLAYER_ATTRIBUTES; i++) {
        memcpy(&received, bytes_received + FLOAT_SIZE * i, FLOAT_SIZE);
        coordinates.push_back(received);
    }
    player.setX(coordinates[0]);
    player.setY(coordinates[1]);
    player.setDirX(coordinates[2]);
    player.setDirY(coordinates[3]);
    view.movePlaneX(coordinates[4]);
    view.movePlaneY(coordinates[5]);
}

// Asigna las coordenadas recibidasa los demas jugadores del mapa.
void Client::_assignOtherPlayersCoordenates(uint8_t *bytes_received,
                                            uint8_t bytes_to_receive,
                                            std::vector<DirectedPositionable> &players,
                                            std::vector<float> &coordinates) {

    float received;
    uint8_t texture;
    int user_size = PLAYER_ATTRIBUTES * FLOAT_SIZE;
    int players_size = ((PLAYERS_ATTRIBUTES - 1) * FLOAT_SIZE + 1);
    int bytes_left = bytes_to_receive - user_size;
    int players_amount = bytes_left / players_size;

    for (int i = 0; i < players_amount; i++) {
        memcpy(&received, bytes_received + user_size + i*players_size, FLOAT_SIZE);
        coordinates.push_back(received);
        memcpy(&received, bytes_received + user_size + i*players_size + FLOAT_SIZE, FLOAT_SIZE);
        coordinates.push_back(received);
        memcpy(&received, bytes_received + user_size + i*players_size + 2*FLOAT_SIZE, FLOAT_SIZE);
        coordinates.push_back(received);
        memcpy(&received, bytes_received + user_size + i*players_size + 3*FLOAT_SIZE, FLOAT_SIZE);
        coordinates.push_back(received);
        memcpy(&texture, bytes_received + user_size + i*players_size + 4*FLOAT_SIZE, 1);
        coordinates.push_back((float)texture);
    }

    for(std::size_t j=PLAYER_ATTRIBUTES; j < coordinates.size(); j+=PLAYERS_ATTRIBUTES){
        std::cout << "Player " << j << ", X: " << coordinates[j] << ", Y: " << coordinates[j+1] <<
        ", dirX: " << coordinates[j+2] <<", dirY: " << coordinates[j+3] << ", tex: " << coordinates[j+4] << std::endl;
        DirectedPositionable other_player(coordinates[j],
                                          coordinates[j + 1],
                                          coordinates[j+2],
                                          coordinates[j+3],
                                          TextureID(coordinates[j+4]));
        players.push_back(other_player);
    }
    std::cout << std::endl;
}



