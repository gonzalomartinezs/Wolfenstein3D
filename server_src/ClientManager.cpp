#include "ClientManager.h"
#include "ThClient.h"

#include <vector>
#include <algorithm>
#include <iostream>

#define KEY_PORT "port"
#define SLEEP_TIME_MILLIS 5
#define MAX_MSG_LEN 1024

#define NEW_GAME 0
#define JOIN_GAME 1

ClientManager::ClientManager(Configuration& config) : config(config),
                socket(NULL, config.getString(KEY_PORT).c_str(), AI_PASSIVE),
                is_connected(true) {
	socket.bind();
}

void ClientManager::operator()(std::vector<Lobby*>& games) {
	socket.listen();

	while (this->is_connected) {
        try {
            ThClient* newClient;
            Peer peer = socket.acceptClient();

            if (this->is_connected) {
                newClient = this->_createClient(peer);
                this->_deleteFinishedGames(games);
                this->_talkWithClient(newClient, games);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
	}
}

uint8_t ClientManager::_blockingRecv(ThClient* client) {
    while (client->isEmpty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_MILLIS));
    }
    return client->pop();
}

ThClient* ClientManager::_createClient(Peer& peer) const {
    ThClient* newClient = new ThClient(peer);
    newClient->start();
    return newClient;
}

void ClientManager::_talkWithClient(ThClient* client, std::vector<Lobby*>& games) {
    uint8_t action, gameID, mapID; //, msg[MAX_MSG_LEN];
    //int msgLen;

    action = _blockingRecv(client);

    if (action == NEW_GAME) {
        /* Enviar mapas disponibles */
        //msgLen = _loadNewGameMsg(msg, games);
        //client->push(msg, msgLen);
        /* - - - */
        mapID = _blockingRecv(client);
        games.push_back(new Lobby(client, this->config, mapID));
        games.back()->start();

    } else if (action == JOIN_GAME) {
        /* Enviar partidas disponibles */
        //msgLen = _loadJoinGameMsg(msg, games);
        //client->push(msg, msgLen);
        /* - - - */
        gameID = _blockingRecv(client);
        if (static_cast<unsigned int>(gameID) >= games.size()) {
            _deleteFailedClient(client);
            throw WolfensteinException("Invalid Game ID, not existing ID\n");

        } else if (games[gameID]->inProgress()) {
            _deleteFailedClient(client);
            throw WolfensteinException("Invalid Game ID, the game is already started\n");

        } else {
            games[gameID]->pushClient(client);
        }

    } else {
        throw WolfensteinException("Invalid action from the client while connecting to server\n");
    }
}

int ClientManager::_loadNewGameMsg(uint8_t* msg, std::vector<Lobby*>& games) {
    uint8_t mapsAmount = 1; //Leer todos los mapas
    std::string mapName = "Mapita";
    uint8_t maxPlayers = 5;
    int currentByte = 1;

    msg[0] = mapsAmount;
    msg[currentByte] = static_cast<uint8_t>(mapName.size());
    currentByte++;

    memcpy(msg + currentByte, mapName.c_str(), mapName.size());
    currentByte += mapName.size();

    msg[currentByte] = maxPlayers;
    currentByte++;

    return currentByte;
}

int ClientManager::_loadJoinGameMsg(uint8_t* msg, std::vector<Lobby*>& games) {
    uint8_t gamesInLobby = 0;
    int currentByte = 1;

    for (long unsigned int i = 0; i < games.size(); i++) {
        if (games[i]->inProgress() == false) {
            msg[currentByte] = i;  // Game ID
            currentByte++;

            msg[currentByte] = static_cast<uint8_t>(games[i]->getMapName().size());
            currentByte++;

            memcpy(msg + currentByte, reinterpret_cast<const uint8_t*>(games[i]->getMapName().c_str()), games[i]->getMapName().size());
            currentByte += games[i]->getMapName().size();

            msg[currentByte] = games[i]->getPlayersAmountInLobby();
            currentByte++;

            msg[currentByte] = games[i]->getMaxPlayers();
            currentByte++;

            gamesInLobby++;
        }
    }
    msg[0] = gamesInLobby;
    return currentByte;
}

/* Devuelve true si el Thread termino su ejecucion, false en
 * caso contrario */
bool _clientHasFinished(Thread* game) {
    if (game->finished() == true) {
        game->join();
        delete game;
        return true;
    }
    return false;
}

void ClientManager::_deleteFinishedGames(std::vector<Lobby*> &games) {
    games.erase(std::remove_if(games.begin(), games.end(), _clientHasFinished), games.end());
}

void ClientManager::_deleteFailedClient(ThClient* client) {
    client->stop();
    client->join();
    delete client;
}

void ClientManager::stop() {
    this->is_connected = false;
    this->socket.stop();
}

ClientManager::~ClientManager() {}