#include "Game.h"
#include "LeaderBoard.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring> //borrar

#define END_GAME_CHAR 0
#define NAME_TIME_TOLERANCE 500
#define SLEEP_TIME_MILLIS 50
#define MAX_MSG_SIZE 256
#define KEY_ITEMS "items"
#define KEY_PLAYER "player"
#define KEY_MAX_PLAYERS "max_players"

const double TICK_DURATION = 1/128.f; // miliseconds que tarda en
                                      // actualizarse el juego

Game::Game(std::vector<ThClient*>& _clients, const Configuration& config,
        const Configuration& config_map) : clients(_clients),
        map(config_map), items(Configuration(config, KEY_ITEMS),
        Configuration(config_map, KEY_ITEMS)), doors(this->map),
    bots_amount(config_map.getInt(KEY_MAX_PLAYERS) - this->clients.size()) {
    this->isRunning = true;

    Configuration config_stats(config, KEY_PLAYER);

    for (size_t i = 0; i < this->clients.size(); ++i) {
        std::string player_number = "player_" + std::to_string(i + 1);
        Configuration config_player(config_map, player_number);
        this->players.push_back(new Player(config_stats, config_player, i));
    }

    for (size_t i = 0; i < this->bots_amount; ++i) {
        std::string player_number = "player_" +
                                    std::to_string(this->clients.size() + i);
        Configuration config_player(config_map, player_number);
        this->players.push_back(new Bot(config_stats, config_player,
                                        this->clients.size() + i));
    }
}

void Game::execute() {
    Timer timeBetweenUpdates;

    this->sendMap();
    //this->recvNames();

    try {
        //Cambiar, ahora es un while true
        // (Esperar caracter para o esperar a que finalice la partida)
        while (this->isRunning) {
            timeBetweenUpdates.start();

            std::cout << "Nuevo Tick" << std::endl;
            this->getInstructions();
            this->sendUpdate();
            this->update();  // Fixed Step-Time

            double lastTickTime = timeBetweenUpdates.getTime();

            if (lastTickTime < TICK_DURATION * 1000) {
                usleep((TICK_DURATION * 1000 - lastTickTime) * 1000);
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Game Loop :(" << std::endl;
    }

    //this->createLeaderBoard();
}

void Game::getInstructions() {
    /* Recibir data de los clientes y actualizar "players" */
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (!this->clients[i]->isEmpty()) {
            uint8_t stateRecv = this->clients[i]->pop();
            this->players[i]->setState(stateRecv);
        }
    }

    for (size_t i = this->clients.size();
        i < this->clients.size() + this->bots_amount; i++) {
        this->players[i]->getState(this->players, i, this->map);
    }
}

void Game::update() {
    for (size_t i = 0; i < this->players.size(); i++) {
        this->players[i]->updatePlayer(this->map, this->items, this->players,
                                        this->doors);
    }

    for (size_t i = 0; i < this->doors.size(); ++i) {
        this->doors[i].update(this->map, this->players);
    }
}

void Game::sendUpdate() {
    /* Enviar update a los clientes */
    uint8_t msg[MAX_MSG_SIZE];
    for (size_t i = 0; i < this->clients.size(); i++) {
        int bytesToSend = this->createMsg(msg, i);
        this->clients[i]->push(msg, bytesToSend);
    }
}

int Game::createMsg(uint8_t* msg, size_t clientNumber) {
    uint8_t texture = Guard_0; //Harcodeado, despeus hacerlo bien
    uint8_t currentByte = 1;

    this->players[clientNumber]->getHUDData(msg + currentByte);
    currentByte += HUD_INFO_SIZE;

    this->players[clientNumber]->getPositionDataWithPlane(msg + currentByte);
    currentByte += POS_DATA_PLANE_SIZE;

    this->items.loadItemsInfo(msg, currentByte);

    for (size_t i = 0; i < this->players.size(); i++) {
        if (i != clientNumber) {
            this->players[i]->getPositionData(msg + currentByte);
            currentByte += POS_DATA_SIZE;

            memcpy(msg + currentByte, &texture, sizeof(uint8_t));
            currentByte += sizeof(uint8_t);
        }
    }
    msg[0] = currentByte - 1;
    return currentByte;
}

void Game::createLeaderBoard() {
    uint8_t endGameChar = END_GAME_CHAR;
    uint8_t msg[MAX_MSG_SIZE];
    uint8_t msgLen;
    LeaderBoard leaderBoard;

    msgLen = leaderBoard.loadLeaderBoard(msg, this->players);

    for (size_t i = 0; i < this->clients.size(); i++) {
        this->clients[i]->push(&endGameChar, 1);
        this->clients[i]->push(&msgLen, 1);
        this->clients[i]->push(msg, msgLen);
    }
}

void _recvName(size_t i, std::vector<ThClient*>& clients,
                std::vector<Player*>& players) {
    std::string name;
    Timer timer;

    timer.start();

    while (clients[i]->isEmpty() && timer.getTime() < NAME_TIME_TOLERANCE) {
        std::this_thread::sleep_for(
                            std::chrono::milliseconds(SLEEP_TIME_MILLIS));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MILLIS));

    if (!clients[i]->isEmpty()) {
        uint8_t size = clients[i]->pop();
        for (int j = 0; j < size; j++) {
            if (!clients[i]->isEmpty()) {
                name.push_back(clients[i]->pop());
            }
        }
        if (name.size() > 0) {
            players[i]->setName(name);
        }
    }

    while (!clients[i]->isEmpty()) {
        clients[i]->pop();
    }
}

void Game::recvNames() {
    std::vector<std::thread*> nameReceivers;

    for (size_t i = 0; i < this->clients.size(); i++) {
        nameReceivers.push_back(new std::thread
        (_recvName, i, std::ref(this->clients), std::ref(this->players)));
    }

    for (size_t i = 0; i < this->clients.size(); i++) {
        nameReceivers[i]->join();
        delete nameReceivers[i];
    }
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

Game::~Game() {
    for (unsigned long int i = 0; i < players.size(); i++) {
        delete players[i];
    }
}
