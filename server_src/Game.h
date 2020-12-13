#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H

#include <atomic>

#include "yaml-cpp/yaml.h"
#include "Player.h"
#include "ThClient.h"
#include "../common_src/Timer.h"
#include "../common_src/Map.h"

class Game {
 private:
    std::vector<Player> players;
    std::vector<ThClient*>& clients;
    std::atomic<bool> isRunning;
    Map map;
    Items items;
 public:
    /* Constructor */
    Game(std::vector<ThClient*>& _clients, const char* file_name);

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
