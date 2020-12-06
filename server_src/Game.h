#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H

#include "Player.h"

class Game {
private:
    std::vector<Player> players;

public:
    /* Constructor */
    Game();

    void update();

    /* Destructor */
    ~Game();

};
#endif  // WOLFENSTEIN3D_GAME_H
