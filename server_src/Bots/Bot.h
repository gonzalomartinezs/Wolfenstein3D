#ifndef WOLFENSTEIN3D_BOT_H
#define WOLFENSTEIN3D_BOT_H

#include <vector>

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

    /* Actualiza el estado del Bot segun lo indique el script de Lua */
    void getState(std::vector<Player*> &players, int botNumber,
                    const Map &map) override;

    /* Destructor */
    ~Bot();

private:
    /* Pushea el mapa al stack de Lua */
    void _pushMap(const Map& map);

    /* Pushea las posiciones del resto de los jugadores al stack de Lua */
    void _pushPlayersPositions(std::vector<Player*> &players, int botNumber);

    /* Pushea la informacion de la posicion y direccion del Bot en cuestion
    al stack de Lua */
    void _pushBotInfo();
};

#endif //WOLFENSTEIN3D_BOT_H
