#include "Game.h"
#include <iostream>
#include <unistd.h>

#define MAX_MSG_SIZE 256

const double TICK_DURATION = 1/30.f; /* miliseconds que tarda en actualizarse el juego */

Game::Game(std::vector<ThClient*>& _clients, const char* file_name) :
            clients(_clients), map(file_name), items(file_name) {
//    YAML::Node file = YAML::LoadFile(file_name);
    this->isRunning = true;
    for (size_t i = 0; i < this->clients.size(); i ++) {
        this->players.emplace_back(0.1, 0.1, 2, 2); //Cambiar (No todos aparecen en la misma posicion)
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
        this->players[i].updatePlayer(this->map, this->items);
    }
}

void Game::sendUpdate() {
    /* Enviar update a los clientes */
    uint8_t msg[MAX_MSG_SIZE];
    int bytesToSend;
    for (size_t i = 0; i < this->clients.size(); i++) {
        bytesToSend = this->createMsg(msg, i);
        this->clients[i]->send(msg, bytesToSend);
    }
}

int Game::createMsg(uint8_t* msg, size_t clientNumber) {
    int playersLoaded = 0;
    this->players[clientNumber].getPositionDataWithPlane(msg + 1);
    for (size_t i = 0; i < this->clients.size() - 1; i++) {
        if (i != clientNumber) {
            this->players[i].getPositionData(msg + 1 + 24 + playersLoaded * 16);
            playersLoaded++;
        }
    }
    msg[0] = 24 + playersLoaded * 16;
    return msg[0] + 1;
}

Game::~Game() {}