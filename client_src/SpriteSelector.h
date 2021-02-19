#ifndef SPRITESELECTOR_H
#define SPRITESELECTOR_H
#include "../common_src/Positionable.h"
#include "../common_src/DirectedPositionable.h"

class SpriteSelector {
public:
    // Crea un selector de sprites listo para ser utilizado.
    SpriteSelector();

    // Selecciona la textura adecuada en funcion de la direccion del jugador
    // y la del  posicionable.
    TextureID selectTexture(DirectedPositionable &player_pos,
                            DirectedPositionable &positionable);

    // LIbera los recursos utilizados por el sprite selector.
    ~SpriteSelector();

private:
   float _calculateAngle(const DirectedPositionable &sprite,
                         const Positionable &player_pos);
};


#endif //SPRITESELECTOR_H
