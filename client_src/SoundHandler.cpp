#include "SoundHandler.h"
#include <cstdlib>
#include <iostream>
#include "sound/SoundID.h"
#include "textures/TextureID.h"
#include "../common_src/GameConstants.h"
#include "../common_src/Doors.h"

#define FOREVER -1
#define LIMIT_DISTANCE 7

enum PlayerInfo {Lives, HP, Weapon, Key, Firing, Ammo, Score};

SoundHandler::SoundHandler(SoundsContainer &sounds, Map &map)
        : sounds(sounds), doors(map){}

void SoundHandler::startBackMusic() {
    Music& music = this->sounds.getMusic(BackMusic);
    music.play(FOREVER);
    music.setVolume(0.2);
}

void SoundHandler::startLeaderBoardMusic() {
    Music& music = this->sounds.getMusic(LB_Music);
    music.play(FOREVER);
    music.setVolume(0.2);
}

void SoundHandler::stopBackMusic() {
    this->sounds.getMusic(BackMusic).stop();
}

void SoundHandler::loadGameSfx(std::vector<int> &player_info,
                               DirectedPositionable &player_pos,
                               std::vector<DirectedPositionable> &positionables,
                               std::vector<int> &doors_states,
                               std::vector<std::pair<int, float>> &sounds) {
    _loadWeaponSfx(player_info);
    _loadMovingObjectsSfx(player_pos, positionables);
    _loadSlidersSfx(player_pos, doors_states);
    _loadRemainingSfx(sounds);
}

void SoundHandler::loadLeaderBoardSfx() {
    usleep(LEADERBOARD_SLEEP_TIME_1);
    this->sounds.getSFX(LB_Title).play();;

    for (int i=0; i<LEADERBOARD_ELEMENTS/3; i++) {
        usleep(LEADERBOARD_SLEEP_TIME_2);
        this->sounds.getSFX(LB_Name).play();
        usleep(LEADERBOARD_SLEEP_TIME_2);
        this->sounds.getSFX(LB_Value).play();
    }
}

SoundHandler::~SoundHandler() {}


// ------------------------- Metodos privados --------------------------------//
// Carga los sfx del arma del jugador.
void SoundHandler::_loadWeaponSfx(std::vector<int> &player_info) {
    if (player_info[Firing]){
        auto id = SoundID(KnifeSFX + player_info[Weapon]);
        this->sounds.getSFX(id).play();
    }
}

// Carga los sfx del arma de los objetos que se mueven por el mapa
void SoundHandler::_loadMovingObjectsSfx(DirectedPositionable &player_pos,
                                         std::vector<DirectedPositionable> &positionables) {
    int i = 0;
    while (i < positionables.size() && i < lastest_positionables.size()){
        if(_hasMoved(positionables[i], lastest_positionables[i])){
            _loadObjectSfx(player_pos, positionables[i]);
        }
        i++;
    }
    while (i < positionables.size()) {
        _loadObjectSfx(player_pos, positionables[i]);
        i++;
    }
    lastest_positionables = positionables;
}

// Reproduce el sonido del posicionable en función de su distancia al jugador.
void SoundHandler::_loadObjectSfx(DirectedPositionable &player_pos,
                                  DirectedPositionable object) {
    float distance = object.distanceTo(player_pos);
    if(distance < LIMIT_DISTANCE) {
        SoundID id;
        TextureID tex = object.getTexture();
        if (tex == Dog_0) id = DogStep;
        else if (tex == Guard_0 || tex == SS_0) id = SoundID(Step_1+rand()%2);
        else id = HeavyStep;
        SoundEffect& sfx = this->sounds.getSFX(id);
        sfx.setVolume(1-distance/(float)LIMIT_DISTANCE);
        sfx.play();
    }
}

// Reproduce los sonidos de los sliders cambiando de estado.
void SoundHandler::_loadSlidersSfx(DirectedPositionable &player_pos,
                                   std::vector<int> &doors_states) {
    for (int i=0; i < doors_states.size(); i++) {
        if (doors_states[i] != doors[i].getState()){
            doors[i].update(doors_states[i]);
            if (doors[i].isOpening() || doors[i].isClosing()) {
                float distance = sqrt(pow(doors[i].getX()-player_pos.getX(),2) +
                                      pow(doors[i].getY()-player_pos.getY(),2));

                if (distance < LIMIT_DISTANCE){
                    SoundID id;
                    if(doors[i].getSurfaceType() == PASSAGE) id = PassageMoving;
                    else id = DoorMoving;
                    SoundEffect& sfx = this->sounds.getSFX(id);
                    sfx.setVolume(1-distance/(float)LIMIT_DISTANCE);
                    sfx.play();
                    sfx.setVolume(1);
                }
            }
        }
    }
}

void SoundHandler::_loadRemainingSfx(std::vector<std::pair<int, float>> &sounds) {
    for(auto& sound: sounds) {
        auto id = SoundID(sound.first);
        SoundEffect& sfx = this->sounds.getSFX(id);
        sfx.setVolume(1-sound.second/(float)LIMIT_DISTANCE);
        sfx.play();
    }
}

// Retorna un booleano indicando si el posicionable se movio entre la primera y
// la segunda posicion.
bool SoundHandler::_hasMoved(DirectedPositionable &first,
                             DirectedPositionable &second) {
    return (abs(first.getX()-second.getX())>0.001 && abs(first.getY()-second.getY())>0.001);
}





