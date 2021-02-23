#ifndef WOLFENSTEIN3D_GAME_H_
#define WOLFENSTEIN3D_GAME_H_

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

    /* Lleva a cabo la ejecución del juego */
    void execute();

    /* Finaliza la ejecución del GameLoop */
    void stop();

    /* Destructor */
    ~Game();

 private:
    /* Desacola una instrucción de cada cliente (Si es que las hay) */
    void getInstructions();

    /* Actualiza todos los elementos del juego en un timeStep */
    void update(double timeSlice);

    /* Envía el correspondiente mensaje a cada uno de los clientes */
    void sendUpdate();

    /* Crea el mensaje correspondiante para cada Player */
    int createMsg(uint8_t* msg, size_t clientNumber, bool hasLost);

    /* Crea y envía la LeaderBoard a cada Player */
    void createLeaderBoard();

    /* Envía el mapa a los clientes */
    void sendMap();

    /* Carga en el mensaje los sonidos que se produjeron en el último update */
    void loadSounds(uint8_t* msg, uint32_t& currentByte, size_t playerNumber);

    /* Devuelve la textura del jugador que le corresponda según el arma */
    TextureID getTexture(uint8_t weapon_id) const;

    /* Devuelve el índice del primer jugador en el vector al que todavía
     * le queden vidas */
    size_t getFirstStillPlayingPlayer();

    /* Devuelve la cantidad de Players a los cuales todavía les queden vidas
     * (Jugadores que no hayan perdido)*/
    size_t livePlayersCounter();
};

#endif  // WOLFENSTEIN3D_GAME_H_
