#include "Game.h"
#include "LeaderBoard.h"
#include "Weapons/WeaponID.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#define END_GAME_PLAYERS 1
#define UINT32_SIZE 4
#define MAX_MSG_SIZE 2048
#define SEND_LEADERBOARD_TOLERANCE 1
#define EPSILON 0.02
#define KEY_ITEMS "items"
#define KEY_PLAYER "player"
#define KEY_MAX_PLAYERS "max_players"
#define KEY_TICK_RATE "tick_rate"
#define KEY_GAME_DURATION "game_duration"

Game::Game(std::vector<ThClient*>& _clients, const Configuration& config,
        const Configuration& config_map) : clients(_clients),
        map(config_map), items(Configuration(config, KEY_ITEMS),
        Configuration(config_map, KEY_ITEMS), this->rockets), doors(this->map),
        bots_amount(config_map.getInt(KEY_MAX_PLAYERS) - this->clients.size()),
        TICK_RATE(1/config.getFloat(KEY_TICK_RATE)), gameDuration(config.getFloat(KEY_GAME_DURATION)){
    this->isRunning = true;

    Configuration config_stats(config, KEY_PLAYER);

    for (size_t i = 0; i < this->clients.size(); ++i) {
        std::string player_number = "player_" + std::to_string(i);
        Configuration config_player(config_map, player_number);
        this->players.push_back(new Player(config_stats, config_player, i,
                                this->clients[i]->getName(), this->sounds));
    }

    for (size_t i = 0; i < this->bots_amount; ++i) {
        std::string player_number = "player_" +
                                    std::to_string(this->clients.size() + i);
        Configuration config_player(config_map, player_number);
        this->players.push_back(new Bot(config_stats, config_player,
                                    this->clients.size() + i, "Bot_" +
                                    std::to_string(i), this->sounds));
    }
}

void Game::execute() {
    Timer timeBetweenUpdates;
    Timer gameTimer;
    this->sendMap();
    float gameDurationMillis = this->gameDuration * 60 * 1000;

    try {
        gameTimer.start();
        while (this->isRunning && gameTimer.getTime() < gameDurationMillis && this->livePlayersCounter() > END_GAME_PLAYERS) {
            timeBetweenUpdates.start();

            this->getInstructions();
            this->sendUpdate();
            this->update(this->TICK_RATE);

            double lastTickTime = timeBetweenUpdates.getTime();

            if (lastTickTime < this->TICK_RATE * 1000) {
                usleep((this->TICK_RATE * 1000 - lastTickTime) * 1000);
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error in Game Loop :(" << std::endl;
    }

    this->createLeaderBoard();
}

void Game::getInstructions() {
    /* Recibir data de los clientes y actualizar "players" */
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (!this->clients[i]->isEmpty()) {
            uint8_t stateRecv = this->clients[i]->pop();
            this->players[i]->setState(stateRecv);
        }
    }

    for (size_t i = this->clients.size();
        i < this->clients.size() + this->bots_amount; i++) {
        this->players[i]->getState(this->players, i, this->map);
    }
}

bool _rocketHasExploded(const Rocket& rocket) {
    return rocket.hasExploded();
}

size_t Game::livePlayersCounter() {
    size_t livePlayers = 0;
    for (size_t i = 0; i < this->players.size(); ++i) {
        if (this->players[i]->hasLost() == false) {
            livePlayers++;
        }
    }
    return livePlayers;
}

void Game::update(double timeSlice) {
    std::vector<Collider> colliders;

    this->rockets.erase(std::remove_if(
            this->rockets.begin(),
            this->rockets.end(),
            _rocketHasExploded), this->rockets.end());

    for (size_t i = 0; i < this->players.size(); i++) {
        this->players[i]->updatePlayer(this->map, this->items, this->players,
                                        this->doors, timeSlice);
        colliders.push_back(this->players[i]->getCollider());
    }

    for (size_t i = 0; i < this->doors.size(); ++i) {
        this->doors[i].update(this->map, colliders);
    }

    for (size_t i = 0; i < this->rockets.size(); ++i) {
        this->rockets[i].update(this->players, this->map, timeSlice);
    }
}

size_t Game::getFirstStillPlayingPlayer() {
    for (size_t i = 0; i < this->players.size(); ++i) {
        if (this->players[i]->hasLost() == false) {
            return i;
        }
    }
    throw GameException("No player left alive\n");
}

void Game::sendUpdate() {
    /* Enviar update a los clientes */
    uint8_t msg[MAX_MSG_SIZE];
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->players[i]->hasLost() == false) {
            int bytesToSend = this->createMsg(msg, i, this->players[i]->hasLost());
            this->clients[i]->push(msg, bytesToSend);

        } else {
            int bytesToSend = this->createMsg(msg, getFirstStillPlayingPlayer(),
                                              this->players[i]->hasLost());
            this->clients[i]->push(msg, bytesToSend);
        }
    }
    this->sounds.clear();
}

int Game::createMsg(uint8_t* msg, size_t clientNumber, bool hasLost) {
    uint32_t currentByte = 4;

    this->players[clientNumber]->getHUDData(msg + currentByte);
    currentByte += HUD_INFO_SIZE;

    memcpy(msg + currentByte, &hasLost, sizeof(bool));
    currentByte += sizeof(bool);

    this->players[clientNumber]->getPositionDataWithPlane(msg + currentByte);
    currentByte += POS_DATA_PLANE_SIZE;

    this->items.loadItemsInfo(msg, currentByte);

    this->loadSounds(msg, currentByte, clientNumber);

    this->doors.loadDoorsInfo(msg, currentByte);

    for (size_t i = 0; i < this->players.size(); i++) {
        if (i != clientNumber) {
            this->players[i]->getPositionData(msg + currentByte);
            currentByte += POS_DATA_SIZE;

            uint8_t texture = Game::getTexture(this->players[i]->\
                                                getWeaponID());

            memcpy(msg + currentByte, &texture, sizeof(uint8_t));
            currentByte += sizeof(uint8_t);
        }
    }

    for (size_t i = 0; i < this->rockets.size(); ++i) {
        this->rockets[i].getPositionData(msg + currentByte);
        currentByte += POS_DATA_SIZE;

        uint8_t texture = this->rockets[i].getTexture();

        memcpy(msg + currentByte, &texture, sizeof(uint8_t));
        currentByte += sizeof(uint8_t);

    }
    uint32_t msgLen = currentByte - 4;
    uint32_t auxEnd = htole32(msgLen);
    memcpy(msg, &auxEnd, sizeof(uint32_t));

    return currentByte;
}

void Game::createLeaderBoard() {
    uint8_t endGameCharBuf[UINT32_SIZE];
    memset(endGameCharBuf, 0, UINT32_SIZE);
    uint8_t msg[MAX_MSG_SIZE];
    uint8_t msgLen;
    LeaderBoard leaderBoard;

    msgLen = leaderBoard.loadLeaderBoard(msg, this->players);

    for (size_t i = 0; i < this->clients.size(); i++) {
        this->clients[i]->push(endGameCharBuf, UINT32_SIZE);
        this->clients[i]->push(&msgLen, 1);
        this->clients[i]->push(msg, msgLen);
    }

    usleep(SEND_LEADERBOARD_TOLERANCE);
}

void Game::stop() {
    this->isRunning = false;
}

void Game::sendMap() {
    uint8_t aux;
    for (long unsigned int k = 0; k < this->clients.size(); k++) {
        aux = uint8_t(this->map.get_n_row());
        this->clients[k]->push(&aux, 1);
        aux = uint8_t(this->map.get_n_col());
        this->clients[k]->push(&aux, 1);
        for (int i = 0; i < this->map.get_n_row(); i++) {
            for (int j = 0; j < this->map.get_n_col(); j++) {
                aux = this->map.get(i, j);
                this->clients[k]->push(&aux, 1);
            }
        }
    }
}

void Game::loadSounds(uint8_t* msg, uint32_t& currentByte, size_t playerNumber) {
    uint8_t size = static_cast<uint8_t>(this->sounds.size());
    uint32_t posByte = currentByte;
    currentByte += sizeof(uint8_t);

    for (size_t i = 0; i < this->sounds.size(); i++) {
        uint8_t sound = this->sounds[i].getSound();
        float distance = this->players[playerNumber]->distanceTo(this->sounds[i]);

        if (distance > EPSILON || sound == PickItemSFX) {
            memcpy(msg + currentByte, &sound, sizeof(uint8_t));
            currentByte += sizeof(uint8_t);

            uint32_t auxEnd = htole32(*reinterpret_cast<uint32_t *>((&distance)));
            memcpy(msg + currentByte, &auxEnd, sizeof(float));
            currentByte += sizeof(float);
        } else {
            size--;
        }
    }
    memcpy(msg + posByte, &size, sizeof(uint8_t));
}

TextureID Game::getTexture(uint8_t weapon_id) const {
    if (weapon_id == KNIFE) return Dog_0;
    if (weapon_id == PISTOL) return Guard_0;
    if (weapon_id == MACHINE_GUN) return SS_0;
    if (weapon_id == CHAIN_GUN) return Officer_0;
    
    return Mutant_0;
}

Game::~Game() {
    for (unsigned long int i = 0; i < players.size(); i++) {
        delete players[i];
    }
}
