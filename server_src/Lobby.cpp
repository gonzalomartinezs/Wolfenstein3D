#include "Lobby.h"
#include <iostream>

#define MAIN_CLIENT 0
#define SLEEP_TIME_MILLIS 5

#define KEY_NAME "map_name"
#define KEY_MAX_PLAYERS "max_players"

Lobby::Lobby(ThClient* mainClient, Configuration &config,
            const std::string& map_file_name) : config(config),
            config_map(map_file_name.c_str()) {
    this->clients.push_back(mainClient);
    this->gameInProgress = false;
    this->gameIsOver = false;
    this->game = NULL;
    this->mapName = config_map.getString(KEY_NAME);
    this->maxPlayers = config_map.getInt(KEY_MAX_PLAYERS);
}

void Lobby::run() {
    while (this->clients[MAIN_CLIENT]->isEmpty() && !this->gameIsOver) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MILLIS));
    }
    if (!this->gameIsOver) {
        this->clients[MAIN_CLIENT]->pop();
        this->_startGame();
    }
    this->_stopClients();
    this->gameIsOver = true;
}

void Lobby::pushClientIfNotInProgress(ThClient* newPlayer) {
    std::unique_lock<std::mutex> lck(this->clientsMtx);
    if (!this->inProgress()) {
        this->clients.push_back(newPlayer);
    } else {
        throw WolfensteinException("Invalid Game ID, the game is already started\n");
    }
}

void Lobby::_startGame() {
    std::unique_lock<std::mutex> lck(this->clientsMtx);
    this->gameInProgress = true;
    lck.unlock();

    try {
        this->game = new Game(this->clients, this->config, this->config_map);
        this->game->execute();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Game :(\n" << std::endl;
    }
}

void Lobby::_stopClients() {
    for (auto client : this->clients) {
        client->stop();
        client->join();
        delete client;
    }
}

uint8_t Lobby::getPlayersAmountInLobby() {
    return this->clients.size();
}

uint8_t Lobby::getMaxPlayers() {
    return this->maxPlayers;
}

std::string Lobby::getMapName() {
    return this->mapName;
}

bool Lobby::inProgress() {
    return this->gameInProgress;
}

void Lobby::stop() {
    if (this->game != NULL) this->game->stop();
    this->gameIsOver = true;
}

bool Lobby::finished() {
    return this->gameIsOver;
}

Lobby::~Lobby() {
    if (this->game != NULL) delete game;
}