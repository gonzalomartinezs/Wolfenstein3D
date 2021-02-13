#include "GamesHandler.h"

GamesHandler::GamesHandler() {}

void GamesHandler::pushGameAndStart(Lobby *newGame) {
    std::unique_lock<std::mutex> lck(this->gamesMtx);
    bool gameAdded = false;
    for (size_t i = 0; i < this->games.size() && !gameAdded; i++) {
        if (this->games[i]->finished()) {
            this->games[i]->join();
            delete this->games[i];
            this->games[i] = newGame;
            this->games[i]->start();
            gameAdded = true;
        }
    }

    if (gameAdded == false) {
        this->games.push_back(newGame);
        this->games.back()->start();
    }
}

void GamesHandler::pushClient(uint8_t gameID, ThClient *newClient) {
    this->games[gameID]->pushClientIfNotInProgress(newClient);
}

void GamesHandler::finishGames() {
    for (auto game : this->games) {
        game->stop();
        game->join();
        delete game;
    }
}

bool GamesHandler::gameInProgress(uint8_t gameID) {
    return this->games[gameID]->inProgress();
}

std::string GamesHandler::getMapName(uint8_t gameID) {
    return this->games[gameID]->getMapName();
}

uint8_t GamesHandler::getPlayersAmountInLobby(uint8_t gameID) {
    return this->games[gameID]->getPlayersAmountInLobby();
}

uint8_t GamesHandler::getMaxPlayers(uint8_t gameID) {
    return this->games[gameID]->getMaxPlayers();
}

size_t GamesHandler::size() {
    return this->games.size();
}

GamesHandler::~GamesHandler() {}