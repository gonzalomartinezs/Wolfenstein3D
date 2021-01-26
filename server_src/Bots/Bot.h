#ifndef WOLFENSTEIN3D_BOT_H
#define WOLFENSTEIN3D_BOT_H

#include "../../common_src/DirectedPositionable.h"
#include "../../common_src/Map.h"
#include "../Player.h"
#include "lua.hpp"

class Bot : public DirectedPositionable {
private:
    lua_State* L;

public:
    /* Constructor */
    Bot(float moveSpeed, float rotSpeed, float posX, float posY);

    void update(std::vector<Player> &players, int botNumber, const Map &map);

    /* Destructor */
    ~Bot();

    void _pushMap(const Map& map);

    void _pushPlayersPositions(std::vector<Player> &players, int botNumber);

    void _pushBotInfo();

};

#endif //WOLFENSTEIN3D_BOT_H
