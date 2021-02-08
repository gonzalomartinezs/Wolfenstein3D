#ifndef WOLFENSTEIN3D_LEADERBOARD_H
#define WOLFENSTEIN3D_LEADERBOARD_H

#define MAX_LEADERBOARD 5

#include "Player.h"

class LeaderBoard {
public:
    /* Constructor */
    LeaderBoard();

    int loadLeaderBoard(uint8_t* msg, std::vector<Player*>& players);

    /* Destructor */
    ~LeaderBoard();

private:
    int _loadKills(uint8_t* msg, std::vector<Player*>& players);
    int _loadScore(uint8_t* msg, std::vector<Player*>& players);
    int _loadBullets(uint8_t* msg, std::vector<Player*>& players);
    void _fillEmptyPlayers(size_t i, uint8_t* msg, int& currentByte);
};

#endif //WOLFENSTEIN3D_LEADERBOARD_H
