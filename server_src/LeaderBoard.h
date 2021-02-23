#ifndef WOLFENSTEIN3D_LEADERBOARD_H_
#define WOLFENSTEIN3D_LEADERBOARD_H_

#define MAX_LEADERBOARD 5

#include <vector>

#include "Player.h"

class LeaderBoard {
public:
    /* Constructor */
    LeaderBoard();

    /* Carga la informacion de la Leaderboard en "msg" y devuelve la cantidad
     * de bytes que ocupa la misma */
    int loadLeaderBoard(uint8_t* msg, std::vector<Player*>& players);

    /* Destructor */
    ~LeaderBoard();

private:
    /* Carga en el mensaje la informacion de las kills de cada jugador */
    int _loadKills(uint8_t* msg, std::vector<Player*>& players);

    /* Carga en el mensaje la informacion del score de cada jugador */
    int _loadScore(uint8_t* msg, std::vector<Player*>& players);

    /* Carga en el mensaje la informacion de la cantidad de balas
     * disparadas por cada jugador */
    int _loadBullets(uint8_t* msg, std::vector<Player*>& players);

    /* Completa cualquier campo (kills, score, bullets) con la de un jugador "Empty" */
    void _fillEmptyPlayers(size_t i, uint8_t* msg, int& currentByte);
};

#endif //WOLFENSTEIN3D_LEADERBOARD_H_
