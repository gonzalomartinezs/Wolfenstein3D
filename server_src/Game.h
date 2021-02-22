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
#include "Weapons/Rocket.h"

class Game {
private:
    std::vector<Player*> players;
    std::vector<ThClient*>& clients;
    std::vector<Sound> sounds;
    std::atomic<bool> isRunning;
    std::vector<Rocket> rockets;
    Map map;
    Items items;
    Doors doors;
    const size_t bots_amount;
    double TICK_RATE;
    float gameDuration;

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

    void update(double timeSlice);

    void sendUpdate();

    int createMsg(uint8_t* msg, size_t clientNumber);

    void createLeaderBoard();

    void sendMap();

    void loadSounds(uint8_t* msg, uint8_t& currentByte, size_t playerNumber);

    TextureID getTexture(uint8_t weapon_id) const;

    size_t getFirstStillPlayingPlayer();

    size_t livePlayersCounter();
};

#endif  // WOLFENSTEIN3D_GAME_H
