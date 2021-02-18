#ifndef WOLFENSTEIN3D_GAME_H
#define WOLFENSTEIN3D_GAME_H

#include <atomic>
#include <vector>

#include "Player.h"
#include "Bots/Bot.h"
#include "ThClient.h"
#include "../common_src/Timer.h"
#include "../common_src/Map.h"
#include "../client_src/textures/TextureID.h"
#include "../common_src/Configuration.h"
#include "../common_src/Doors.h"

class Game {
private:
    std::vector<Player*> players;
    std::vector<ThClient*>& clients;
    std::atomic<bool> isRunning;
    Map map;
    Items items;
    Doors doors;
    const size_t bots_amount;

public:
    /* Constructor */
    Game(std::vector<ThClient*>& _clients, const Configuration& config,
        const Configuration& config_map);

    void execute();

    void stop();

    /* Destructor */
    ~Game();

 private:
    void getInstructions();

    void update();

    void sendUpdate();

    int createMsg(uint8_t* msg, size_t clientNumber);

    void createLeaderBoard();

    void sendMap();
};

#endif  // WOLFENSTEIN3D_GAME_H
