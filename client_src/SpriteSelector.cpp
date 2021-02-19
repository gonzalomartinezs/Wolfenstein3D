#include "SpriteSelector.h"
#include <math.h>
#include <iostream>

#define PI 3.141592
#define TEXTURES_AMOUNT 8


SpriteSelector::SpriteSelector() {}

TextureID SpriteSelector::selectTexture(DirectedPositionable &player_pos,
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
