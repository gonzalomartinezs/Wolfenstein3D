#include "Game.h"
#include <iostream>
#include <unistd.h>
#include <cstring> //borrar

#define MAX_MSG_SIZE 256
#define KEY_ITEMS "items"
#define KEY_PLAYER "player"

const double TICK_DURATION = 1/128.f; /* miliseconds que tarda en actualizarse el juego */

Game::Game(std::vector<ThClient*>& _clients, const Configuration& config,
            const Configuration& config_map) : clients(_clients),
            map(config_map), items(Configuration(config, KEY_ITEMS),
            Configuration(config_map, KEY_ITEMS)) {
    this->isRunning = true;

    Configuration config_stats_player(config, KEY_PLAYER);

    this->players.reserve(10);
    for (size_t i = 0; i < this->clients.size(); ++i) {
        std::string player_number = "player_" + std::to_string(i + 1);
        Configuration config_player(config_map, player_number);
        this->players.emplace_back(config_stats_player, config_player, i);
    }
}

void Game::execute() {

    Timer timeBetweenUpdates;
    double lastTickTime = 0;

    try {
        while (this->isRunning) { //Cambiar, ahora es un while true (Esperar caracter para o esperar a que finalice la partida)
            timeBetweenUpdates.start();

            std::cout << "Nuevo Tick" << std::endl;
            this->getInstructions();
            this->update();  // Fixed Step-Time
            this->sendUpdate();

            timeBetweenUpdates.getTime();

            if (lastTickTime < TICK_DURATION * 1000) {
                usleep((TICK_DURATION * 1000 - lastTickTime) * 1000);
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Game Loop :(" << std::endl;
    }
}

void Game::getInstructions() {
    /* Recibir data de los clientes y actualizar "players" */
    uint8_t stateRecv = -1;
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (!this->clients[i]->isEmpty()) {
            stateRecv = this->clients[i]->pop();
            this->players[i].setState(stateRecv);
        }
    }
}

void Game::update() {
    for (size_t i = 0; i < this->players.size(); i++) {
        this->players[i].updatePlayer(this->map, this->items, this->players);
    }
}

void Game::sendUpdate() {
    /* Enviar update a los clientes */
    uint8_t msg[MAX_MSG_SIZE];
    int bytesToSend;
    for (size_t i = 0; i < this->clients.size(); i++) {
        bytesToSend = this->createMsg(msg, i);
        this->clients[i]->push(msg, bytesToSend);
    }
}

int Game::createMsg(uint8_t* msg, size_t clientNumber) {
    int playersLoaded = 0;
    uint8_t texture = Guard_0; //Harcodeado, despeus hacerlo bien

    this->players[clientNumber].getHUDData(msg+1);

    this->players[clientNumber].getPositionDataWithPlane(msg + 1 + HUD_INFO_SIZE);
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (i != clientNumber) {
            this->players[i].getPositionData(msg + 1 + 24 + playersLoaded * 17 + HUD_INFO_SIZE); // era *16 sin el hardcodeo del guard
            memcpy(msg + 1 + 24 + playersLoaded * 17 + 16 + HUD_INFO_SIZE, &texture, 1); //harcodeado, despues hacerlo bien
            playersLoaded++;
        }
    }
    msg[0] = 24 + playersLoaded * 17 + HUD_INFO_SIZE;
    return msg[0] + 1;
}

void Game::stop() {
    this->isRunning = false;
}

void Game::sendMap() {
    uint8_t aux;
    for (long unsigned int k = 0; k < this->clients.size(); k++) {
        aux = uint8_t(this->map.get_n_row());
        this->clients[k]->push(&aux, 1);
        aux = uint8_t(this->map.get_n_col());
        this->clients[k]->push(&aux, 1);
        for (int i = 0; i < this->map.get_n_row(); i++) {
            for (int j = 0; j < this->map.get_n_col(); j++) {
                aux = this->map.get(i, j);
                this->clients[k]->push(&aux, 1);
            }
        }
    }
}

Game::~Game() {}