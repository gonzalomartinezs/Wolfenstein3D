#include "SpriteSelector.h"
#include <math.h>
#include <iostream>

#define PI 3.141592
#define TEXTURES_AMOUNT 8
#define MOVED 1
#define NOT_MOVED 0

SpriteSelector::SpriteSelector(TexturesContainer &tex): tex(tex) {}


void SpriteSelector::initializePlayers(std::vector<DirectedPositionable> &players) {
    this->players = players;
    this->latest_players = players;
    dynamic_tex.clear();
    for (auto& player: players) {
        if(player.getTexture() >= Dog_0)
            dynamic_tex.emplace_back(tex.getDynamic(player.getTexture()), false);
    }
}


void SpriteSelector::updatePlayers(std::vector<DirectedPositionable> &players) {
    this->latest_players = this->players;
    this->players = players;
}


TextureID SpriteSelector::selectTextureID(DirectedPositionable &player_pos,
                                          DirectedPositionable &positionable) {

    float gamma = _calculateAngle(positionable, player_pos);
    int offset = int((gamma+PI/16)*(4/PI))%TEXTURES_AMOUNT;

    return TextureID(positionable.getTexture()+offset);
}

SpriteSelector::~SpriteSelector() {}

// ------------------------- Metodos privados --------------------------------//

// Retorna el angunlo de incidencia entre el jugador y la direccion del sprite.
float SpriteSelector::_calculateAngle(const DirectedPositionable &sprite,
                                      const Positionable &player_pos) {

    // teorema del coseno: c^2 = a^2 + b^2 - 2*a*b*cos(gamma)
    Positionable aux(sprite.getX() + sprite.getDirX(), sprite.getY() + sprite.getDirY(), None);
    float a = player_pos.distanceTo((Positionable &) sprite);
    float b = sprite.distanceTo(aux);
    float c = player_pos.distanceTo(aux);

    float gamma = acos((-pow(c, 2) + pow(a, 2) + pow(b,2))/( 2 * a * b ));
    // y = slope * x + intercept
    float x_diff = sprite.getX()-player_pos.getX();
    if (x_diff != 0){
        float slope = (sprite.getY()-player_pos.getY()) / x_diff;
        float intercept = player_pos.getY() - player_pos.getX() * slope;
        float directed_y = sprite.getY() + sprite.getDirY();
        float expected_y = (sprite.getX()+sprite.getDirX())*slope+intercept;

        if ((player_pos.getX() >= sprite.getX() && directed_y <= expected_y) ||
            (player_pos.getX() < sprite.getX() && directed_y > expected_y))
            gamma = 2*PI - gamma;

    } else {
        if ((player_pos.getY() <= sprite.getY() &&
             sprite.getX() + sprite.getDirX() < player_pos.getX()) ||
            (player_pos.getY() > sprite.getY() &&
             sprite.getX() + sprite.getDirX() >= player_pos.getX()))
            gamma = 2*PI - gamma;
    }
    return gamma;
}

Texture *SpriteSelector::selectTexture(Positionable &positionable) {
    TextureID tex_id = positionable.getTexture();
    if (tex_id >= Dog_0) {
        int i = 0;
        for(auto& player: players) {
            if (player.distanceTo(positionable) < 0.01) break;
            i++;
        }
        TextureSet* new_set = tex.getDynamic(tex_id);
        dynamic_tex[i].updateSet(new_set);
        int state = (players[i].distanceTo(latest_players[i]) > 0.01) ? MOVED: NOT_MOVED;
        return dynamic_tex[i].getTexture(state);
    //} else if (positionable.getTexture() > Missile_0) {
    } else {
        return tex.getStatic(tex_id);
    }
}

