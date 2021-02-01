#include <cstring>
#include <sstream>
#include <string>
#include <iostream>
#include "Client.h"
#include "../common_src/GameConstants.h"
#define FLOAT_SIZE sizeof(float)
#define UINT_ATTRIBUTES 4
#define INT_ATTRIBUTES 2
#define PLAYER_INFO 4 + 2 * sizeof(int) // lives, hp, key, weapon, ammo(int), score(int)
#define PLAYER_ATTRIBUTES 6
#define OTHER_PLAYERS_ATTRIBUTES 5
#define MAX_MESSAGE_SIZE 256

Client::Client(std::string host, std::string service,
               BlockingQueue<int> &instructions,
               ProtectedQueue<DrawingInfo> &drawing_info):
        socket(host.c_str(), service.c_str(), 0),
        peer(socket.connect()), instructions(instructions),
        drawing_info(drawing_info), is_connected(true) {}


void Client::sendInstruction() {
    ssize_t sent = 0;
    try{
        while (is_connected && sent >= 0 && !instructions.isWorking()){
            uint8_t instruction = this->instructions.pop();
            sent = this->peer.send(&instruction, sizeof(uint8_t));
        }
    } catch (WolfensteinException& e){}
    std::cout<<"fin send\n";
}

ssize_t Client::receiveInformation() {
    while(is_connected){
        uint8_t bytes_to_receive;
        uint8_t bytes_received[MAX_MESSAGE_SIZE]; //almacena info recibida
        memset(bytes_received, 0, MAX_MESSAGE_SIZE);

        this->peer.recv(&bytes_to_receive, 1);
        this->peer.recv(bytes_received, bytes_to_receive);
        DirectedPositionable player(0, 0, 0, 0, None);
        PlayerView view;
        std::vector<float> coordinates;
        std::vector<int> player_info;
        std::vector<Positionable> objects;
        std::vector<DirectedPositionable> directed_objects; // jugadores y objetos moviles
        std::vector<std::tuple<int,int,int>> doors_changes;
        _assignPlayerInfo(player_info, bytes_received);
        _assignPlayerCoordenates(player, view, coordinates,
                                 bytes_received);
        _assignOtherPlayersCoordenates(bytes_received, bytes_to_receive, directed_objects, coordinates);
        DrawingInfo new_info(player, view, player_info,objects, directed_objects, doors_changes);
        this->drawing_info.push(new_info);
    }
    std::cout<<"fin recv\n";
    return 0;
}


void Client::shutdown() {
    this->is_connected = false;
    this->socket.stop();
    this->instructions.doneAdding();
}

Client::~Client() {
    if (is_connected) shutdown();
}


//-------------------------- Metodos privados --------------------------------//
// Asigna la informacion del jugador (vida, balas, arma, ...) a sus atributos
void Client::_assignPlayerInfo(std::vector<int> &info, uint8_t *bytes_received) {
    uint8_t received_uint8;
    int received_int;
    for(int i=0; i< UINT_ATTRIBUTES; i++){
        memcpy(&received_uint8, bytes_received + i * sizeof(uint8_t), sizeof(uint8_t));
        info.push_back(int(received_uint8));
    }
    for(int i=0; i< INT_ATTRIBUTES; i++){
        memcpy(&received_int, bytes_received +
                UINT_ATTRIBUTES*sizeof(uint8_t) + i*sizeof(int), sizeof(int)); //ammo
        info.push_back(received_int);
    }
}

// Asigna las coordenadas recibidas a los atributos del jugador
void
Client::_assignPlayerCoordenates(DirectedPositionable &player, PlayerView &view,
                                 std::vector<float> &coordinates,
                                 uint8_t *bytes_received) {
    float received;
    for (std::size_t i = 0; i < PLAYER_ATTRIBUTES; i++) {
        memcpy(&received, bytes_received + PLAYER_INFO + FLOAT_SIZE * i, FLOAT_SIZE);
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
    int user_size = PLAYER_ATTRIBUTES * FLOAT_SIZE + PLAYER_INFO;
    int players_size = ((OTHER_PLAYERS_ATTRIBUTES - 1) * FLOAT_SIZE + 1);
    int players_amount = (bytes_to_receive - user_size) / players_size;

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

    for(std::size_t j=PLAYER_ATTRIBUTES; j < coordinates.size(); j+=OTHER_PLAYERS_ATTRIBUTES){
        DirectedPositionable other_player(coordinates[j],
                                          coordinates[j + 1],
                                          coordinates[j+2],
                                          coordinates[j+3],
                                          TextureID(coordinates[j+4]));
        players.push_back(other_player);
    }
}




