#include "ClientHandler.h"
#include <iostream>
#include <cstring>
#include <string>

#define ERROR -1
#define MAX_MSG_LEN 1024
#define NEW_GAME 0
#define JOIN_GAME 1
#define SLEEP_TIME_MILLIS 5

ClientHandler::ClientHandler(ThClient* newClient, GamesHandler& games,
                            Configuration& config) : games(games),
                            config(config) {
    this->newClient = newClient;
    this->endTalking = false;
}

void ClientHandler::run() {
    try {
        this->_talkWithClient();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        _deleteFailedClient();
    }
    this->endTalking = true;
}

void ClientHandler::_talkWithClient() {
    uint8_t action, gameID, msg[MAX_MSG_LEN];
    int msgLen;

    action = this->_blockingRecv();

    if (action == NEW_GAME && !this->endTalking) {
        MapsReader maps_reader(MAPS_FOLDER_PATH);

        msgLen = _loadNewGameMsg(msg, maps_reader);
        this->newClient->push(msg, msgLen);

        uint8_t mapID = _blockingRecv();

        if (!this->endTalking) {
            games.pushGameAndStart(new Lobby(this->newClient, this->config,
                                    maps_reader.getFileName(mapID)));
        } else {
            throw WolfensteinException("Connection ended, server closed"
                                    " (Choosing Map in a New Game)\n");
        }

    } else if (action == JOIN_GAME && !this->endTalking) {
        msgLen = _loadJoinGameMsg(msg);
        this->newClient->push(msg, msgLen);

        gameID = _blockingRecv();

        if (!this->endTalking) {
            if (static_cast<unsigned int>(gameID) >= this->games.size()) {
                throw WolfensteinException("Invalid Game ID,"
                                            " not existing ID\n");
            } else {
                this->games.pushClient(gameID, this->newClient);
            }
        } else {
            throw WolfensteinException("Connection ended, server closed"
                                        " (Choosing game ID) \n");
        }
    } else {
        throw WolfensteinException("Invalid action from the client or"
                                    " server closed (New/Join)\n");
    }
}

int ClientHandler::_loadNewGameMsg(uint8_t* msg,
                                    const MapsReader& maps_reader) {
    msg[0] = static_cast<uint8_t>(maps_reader.size());
    int currentByte = 1;

    for (size_t i = 0; i < maps_reader.size(); ++i) {
        std::string map_name = maps_reader.getName(i);
        msg[currentByte] = static_cast<uint8_t>(map_name.size());
        currentByte++;

        memcpy(msg + currentByte, map_name.c_str(), map_name.size());
        currentByte += map_name.size();

        msg[currentByte] = maps_reader.getMaxPlayers(i);
        currentByte++;
    }

    return currentByte;
}

int ClientHandler::_loadJoinGameMsg(uint8_t* msg) {
    uint8_t gamesInLobby = 0;
    int currentByte = 1;

    for (long unsigned int i = 0; i < this->games.size(); i++) {
        if (games.gameInProgress(i) == false) {
            msg[currentByte] = i;  // Game ID
            currentByte++;

            msg[currentByte] = static_cast<uint8_t>(
                                                games.getMapName(i).size());
            currentByte++;

            memcpy(msg + currentByte,
                reinterpret_cast<const uint8_t*>(games.getMapName(i).c_str()),
                games.getMapName(i).size());
            currentByte += games.getMapName(i).size();

            msg[currentByte] = games.getPlayersAmountInLobby(i);
            currentByte++;

            msg[currentByte] = games.getMaxPlayers(i);
            currentByte++;

            gamesInLobby++;
        }
    }
    msg[0] = gamesInLobby;
    return currentByte;
}

void ClientHandler::_deleteFailedClient() {
    this->newClient->stop();
    this->newClient->join();
    delete this->newClient;
}

uint8_t ClientHandler::_blockingRecv() {
    while (this->newClient->isEmpty() && !this->endTalking) {
        std::this_thread::sleep_for(
                        std::chrono::milliseconds(SLEEP_TIME_MILLIS));
    }
    /* Evito warnings sobre comportamiento indefinido (Valgrind) */
    if (this->endTalking) {
        return ERROR;
    }
    /* - - - - - - - - - - - - - - - - - - - - - - - */
    return this->newClient->pop();
}

void ClientHandler::stop() {
    this->endTalking = true;
}

bool ClientHandler::finished() {
    return this->endTalking;
}

ClientHandler::~ClientHandler() {}
