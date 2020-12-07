#include "Game.h"
#include <iostream>
#include <unistd.h>

const double TICK_DURATION = 1/60.f; /* miliseconds que tarda en actualizarse el juego */

Game::Game(std::vector<ThClient*>& clients) : clients(clients) {
    this->isRunning = true;
    for (int i = 0; i < this->clients.size(); i ++) {
        this->players.emplace_back(0.1, 0.1, 2, 2);
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
            this->update();
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
    /* Recibir data de los clientes y actualizar players */
    uint8_t stateRecv;
    for (int i = 0; i < this->clients.size(); i++) {
        if (this->clients[i].isEmpty) {
            stateRecv = this->clients[i].pop();
        }
        this->players[i].setState(stateRecv);
    }
}

void Game::update() {
    for (int i = 0; i < this->players.size(); i++) {
        this->players[i].updatePlayer();
    }
}

void Game::sendUpdate() {
    /*Enviar update a los clientes*/
}

Game::~Game() {}