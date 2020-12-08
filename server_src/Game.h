#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H

#include <atomic>

#include "Player.h"
#include "ThClient.h"
#include "../common_src/Timer.h"

class Game {
 private:
    std::vector<Player> players;
    std::vector<ThClient*>& clients;
    std::atomic<bool> isRunning;

 public:
    /* Constructor */
    Game(std::vector<ThClient*>& clients);

    void execute();

    /* Destructor */
    ~Game();

 private:
    void getInstructions();

    void update();

    void sendUpdate();

    int createMsg(uint8_t* msg, size_t clientNumber);
};

#endif  // WOLFENSTEIN3D_GAME_H
