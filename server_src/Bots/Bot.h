#ifndef WOLFENSTEIN3D_BOT_H
#define WOLFENSTEIN3D_BOT_H

#include "../../common_src/Map.h"
#include "../Player.h"
#include "lua.hpp"

class Bot : public Player {
private:
    lua_State* L;

public:
    /* Constructor */
    Bot(const Configuration& config_stats,
        const Configuration& config_map,
        const uint8_t _player_number);

    void getState(std::vector<Player*> &players, int botNumber, const Map &map) override;

    /* Destructor */
    ~Bot();

private:

    void _pushMap(const Map& map);

    void _pushPlayersPositions(std::vector<Player*> &players, int botNumber);

    void _pushBotInfo();
};

#endif //WOLFENSTEIN3D_BOT_H
