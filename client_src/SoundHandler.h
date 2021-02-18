#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <vector>
#include "sound/SoundsContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/SlidingSurface.h"

class SoundHandler {
private:
    SoundsContainer& sounds;
    std::vector<DirectedPositionable> lastest_positionables;
    std::vector<SlidingSurface> sliders;
    int last_ammo;

public:
    // Crea un handler de sonidos listo para ser utilizado.
    SoundHandler(SoundsContainer& sounds, std::vector<SlidingSurface> sliders);

    // Comienza la reproduccion de la musica de fondo del juego.
    void startBackMusic();

    void
    loadGameSfx(std::vector<int> &player_info, DirectedPositionable &player_pos,
                std::vector<DirectedPositionable> &positionables,
                std::vector<std::pair<int, int>> & sliders);

    // Libera los recursos utilizados por el objeto.
    ~SoundHandler();

private:
    void _loadWeaponSfx(std::vector<int> &player_info);
    void _loadMovingObjectsSfx(DirectedPositionable &player_pos,
                               std::vector<DirectedPositionable> &positionables);
    void _loadSlidersSfx(DirectedPositionable &player_pos, std::vector<std::pair<int, int>> &sliders);
    void _loadObjectSfx(DirectedPositionable &player_pos, DirectedPositionable object);
    bool _hasMoved(DirectedPositionable& first, DirectedPositionable& second);
};


#endif //WOLFENSTEINCLIENT_SOUNDHANDLER_H
