#include "LeaderBoard.h"
#include <cstring>

LeaderBoard::LeaderBoard() {}

int LeaderBoard::loadLeaderBoard(uint8_t* msg, std::vector<Player*>& players) {
    uint8_t bytes = 0;
    bytes += _loadKills(msg, players);
    bytes += _loadScore(msg + bytes, players);
    bytes += _loadBullets(msg + bytes, players);
    return bytes;
}

int LeaderBoard::_loadKills(uint8_t* msg, std::vector<Player*>& players) {
    std::string str, empty = "Empty";
    int aux, emptyValue = 0;
    Player* swap;
    uint8_t currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            if (players[j]->getKills() > players[j+1]->getKills()) {
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

    for (; i < MAX_LEADERBOARD; i++) {
        msg[currentByte] = static_cast<uint8_t>(empty.size());
        currentByte++;

        memcpy(msg + currentByte, empty.c_str(), empty.size());
        currentByte += empty.size();

        memcpy(msg + currentByte, &emptyValue, sizeof(int));
        currentByte += sizeof(int);
    }

    return currentByte;
}

int LeaderBoard::_loadScore(uint8_t* msg, std::vector<Player*>& players) {
    std::string str, empty = "Empty";
    int aux, emptyValue = 0;
    Player* swap;
    uint8_t currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            if (players[j]->getScore() > players[j+1]->getScore()) {
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

    for (; i < MAX_LEADERBOARD; i++) {
        msg[currentByte] = static_cast<uint8_t>(empty.size());
        currentByte++;

        memcpy(msg + currentByte, empty.c_str(), empty.size());
        currentByte += empty.size();

        memcpy(msg + currentByte, &emptyValue, sizeof(int));
        currentByte += sizeof(int);
    }

    return currentByte;
}

int LeaderBoard::_loadBullets(uint8_t* msg, std::vector<Player*>& players) {
    std::string str, empty = "Empty";
    int aux, emptyValue = 0;
    Player* swap;
    uint8_t currentByte = 0;

    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = 0; j < players.size(); j++) {
            if (players[j]->getBulletsFired()> players[j+1]->getBulletsFired()) {
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

    for (; i < MAX_LEADERBOARD; i++) {
        msg[currentByte] = static_cast<uint8_t>(empty.size());
        currentByte++;

        memcpy(msg + currentByte, empty.c_str(), empty.size());
        currentByte += empty.size();

        memcpy(msg + currentByte, &emptyValue, sizeof(int));
        currentByte += sizeof(int);
    }

    return currentByte;
}

LeaderBoard::~LeaderBoard() {}