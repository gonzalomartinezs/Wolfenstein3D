#include "SoundHandler.h"
#include <cstdlib>
#include <iostream>
#include "sound/SoundID.h"
#include "textures/TextureID.h"
#include "../common_src/GameConstants.h"

#define FOREVER -1
#define LIMIT_DISTANCE 7

enum PlayerInfo {Lives, HP, Weapon, Key, Firing, Ammo, Score};

SoundHandler::SoundHandler(SoundsContainer &sounds, std::vector<SlidingSurface> sliders):
                                        sounds(sounds), sliders(sliders), last_ammo(0){}

void SoundHandler::startBackMusic() {
    Music& music = this->sounds.getMusic(BackMusic);
    music.play(FOREVER);
    music.setVolume(0.2);
}

void SoundHandler::loadGameSfx(std::vector<int> &player_info,
                               DirectedPositionable &player_pos,
                               std::vector<DirectedPositionable> &positionables,
                               std::vector<std::pair<int, int>> &sliders) {
    _loadWeaponSfx(player_info);
    _loadMovingObjectsSfx(player_pos, positionables);
//    _loadSlidersSfx(player_pos, sliders);
}

SoundHandler::~SoundHandler() {}


// ------------------------- Metodos privados --------------------------------//
// Carga los sfx del arma del jugador.
void SoundHandler::_loadWeaponSfx(std::vector<int> &player_info) {
    if (last_ammo > player_info[Ammo] || (player_info[Weapon] == 0 && player_info[Firing])){
        auto id = SoundID(KnifeSFX + player_info[Weapon]);
        this->sounds.getSFX(id).play(0);
    }
    last_ammo = player_info[Ammo];
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
        sfx.play(0);
        sfx.setVolume(1);
    }
}

// Reproduce los sonidos de los sliders cambiando de estado.
void SoundHandler::_loadSlidersSfx(DirectedPositionable &player_pos,
                                   std::vector<std::pair<int, int>> &sliders_changes) {
    for (int i=0; i<sliders_changes.size(); i++) {
        if (sliders_changes[i].second != sliders[i].getState()){
            sliders[i].update(sliders_changes[i].second);

            if (sliders[i].isOpening() || sliders[i].isClosing()) {
                float distance = sqrt(pow(sliders[i].getX()-player_pos.getX(),2) +
                                      pow(sliders[i].getY()-player_pos.getY(),2));

                if (distance < LIMIT_DISTANCE){
                    SoundID id;
                    if(sliders[i].getSurfaceType() == DOOR) id = DoorMoving;
                    else id = PassageMoving;
                    SoundEffect& sfx = this->sounds.getSFX(id);
                    sfx.setVolume(1-distance/(float)LIMIT_DISTANCE);
                    sfx.play(0);
                    sfx.setVolume(1);
                }
            }
        }
    }
}

// Retorna un booleano indicando si el posicionable se movio entre la primera y
// la segunda posicion.
bool SoundHandler::_hasMoved(DirectedPositionable &first,
                             DirectedPositionable &second) {
    return (abs(first.getX()-second.getX())>0.001 && abs(first.getY()-second.getY())>0.001);
}



