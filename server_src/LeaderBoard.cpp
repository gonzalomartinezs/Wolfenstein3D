#include "LeaderBoard.h"
#include <vector>
#include <string>
#include <cstring>

LeaderBoard::LeaderBoard() {}

int LeaderBoard::loadLeaderBoard(uint8_t* msg, std::vector<Player*>& players) {
    int bytes = 0;
    bytes += _loadKills(msg, players);
    bytes += _loadScore(msg + bytes, players);
    bytes += _loadBullets(msg + bytes, players);
    return bytes;
}

int LeaderBoard::_loadKills(uint8_t* msg, std::vector<Player*>& players) {
    std::string str;
    int aux;
    Player* swap;
    int currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size() - 1; j++) {
            if (players[j]->getKills() < players[j+1]->getKills()) {
                swap = players[j];
                players[j] = players[j+1];
                players[j+1] = swap;
            }
        }
    }

    size_t i;

    for (i = 0; i < players.size() && i < MAX_LEADERBOARD; i++) {
        str = players[i]->getName();
        aux = players[i]->getKills();

        msg[currentByte] = static_cast<uint8_t>(str.size());
        currentByte++;

        memcpy(msg + currentByte, str.c_str(), str.size());
        currentByte += str.size();

        memcpy(msg + currentByte, &aux, sizeof(int));
        currentByte += sizeof(int);
    }

    this->_fillEmptyPlayers(i, msg, currentByte);

    return currentByte;
}

int LeaderBoard::_loadScore(uint8_t* msg, std::vector<Player*>& players) {
    std::string str;
    int aux;
    Player* swap;
    int currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size() - 1; j++) {
            if (players[j]->getScore() < players[j+1]->getScore()) {
                swap = players[j];
                players[j] = players[j+1];
                players[j+1] = swap;
            }
        }
    }

    size_t i;

    for (i = 0; i < players.size() && i < MAX_LEADERBOARD; i++) {
        str = players[i]->getName();
        aux = players[i]->getScore();

        msg[currentByte] = static_cast<uint8_t>(str.size());
        currentByte++;

        memcpy(msg + currentByte, str.c_str(), str.size());
        currentByte += str.size();

        memcpy(msg + currentByte, &aux, sizeof(int));
        currentByte += sizeof(int);
    }

    this->_fillEmptyPlayers(i, msg, currentByte);

    return currentByte;
}

int LeaderBoard::_loadBullets(uint8_t* msg, std::vector<Player*>& players) {
    std::string str;
    int aux;
    Player* swap;
    int currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size() - 1; j++) {
            if (players[j]->getBulletsFired() <
                players[j+1]->getBulletsFired()) {
                swap = players[j];
                players[j] = players[j+1];
                players[j+1] = swap;
            }
        }
    }

    size_t i;

    for (i = 0; i < players.size() && i < MAX_LEADERBOARD; i++) {
        str = players[i]->getName();
        aux = players[i]->getBulletsFired();

        msg[currentByte] = static_cast<uint8_t>(str.size());
        currentByte++;

        memcpy(msg + currentByte, str.c_str(), str.size());
        currentByte += str.size();

        memcpy(msg + currentByte, &aux, sizeof(int));
        currentByte += sizeof(int);
    }

    this->_fillEmptyPlayers(i, msg, currentByte);

    return currentByte;
}

void LeaderBoard::_fillEmptyPlayers(size_t i, uint8_t *msg, int& currentByte) {
    std::string empty = "Empty";
    int emptyValue = 0;

    for (; i < MAX_LEADERBOARD; i++) {
        msg[currentByte] = static_cast<uint8_t>(empty.size());
        currentByte++;

        memcpy(msg + currentByte, empty.c_str(), empty.size());
        currentByte += empty.size();

        memcpy(msg + currentByte, &emptyValue, sizeof(int));
        currentByte += sizeof(int);
    }
}

LeaderBoard::~LeaderBoard() {}
