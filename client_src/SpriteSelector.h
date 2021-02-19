#ifndef SPRITESELECTOR_H
#define SPRITESELECTOR_H

#include <vector>
#include "../common_src/Positionable.h"
#include "../common_src/DirectedPositionable.h"
#include "textures/DynamicTexture.h"
#include "textures/TexturesContainer.h"

class SpriteSelector {
private:
    TexturesContainer& tex;
    std::vector<DirectedPositionable> players;
    std::vector<DirectedPositionable> latest_players;
    std::vector<DynamicTexture> dynamic_tex;

public:
    // Crea un selector de sprites listo para ser utilizado.
    explicit SpriteSelector(TexturesContainer& tex);

    // Inicializa las texturas relacionadas a los jugadores.
    void initializePlayers(std::vector<DirectedPositionable>& players);

    // Actualiza los juagadores.
    void updatePlayers(std::vector<DirectedPositionable>& players);

    // Selecciona la textura adecuada en funcion de la direccion del jugador
    // y la del  posicionable.
    TextureID selectTextureID(DirectedPositionable &player_pos,
                              DirectedPositionable &positionable);

    Texture* selectTexture(Positionable& positionable);

    // LIbera los recursos utilizados por el sprite selector.
    ~SpriteSelector();

private:
   float _calculateAngle(const DirectedPositionable &sprite,
                         const Positionable &player_pos);
};


#endif //SPRITESELECTOR_H
