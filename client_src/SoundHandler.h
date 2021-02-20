#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <vector>
#include "sound/SoundsContainer.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/SlidingSurface.h"
#include "../common_src/Doors.h"

class SoundHandler {
private:
    SoundsContainer& sounds;
    std::vector<DirectedPositionable> lastest_positionables;
    Doors doors;

public:
    // Crea un handler de sonidos listo para ser utilizado.
    SoundHandler(SoundsContainer &sounds, Map &map);

    // Comienza la reproduccion de la musica de fondo del juego.
    void startBackMusic();

    void
    loadGameSfx(std::vector<int> &player_info, DirectedPositionable &player_pos,
                std::vector<DirectedPositionable> &positionables,
                std::vector<int> &doors_states,
                std::vector<std::pair<int, float>> &sounds);

    // Libera los recursos utilizados por el objeto.
    ~SoundHandler();

private:
    void _loadWeaponSfx(std::vector<int> &player_info);
    void _loadMovingObjectsSfx(DirectedPositionable &player_pos,
                               std::vector<DirectedPositionable> &positionables);
    void _loadSlidersSfx(DirectedPositionable &player_pos, std::vector<int> &doors_states);
    void _loadRemainingSfx(std::vector<std::pair<int, float>> &sounds);
    void _loadObjectSfx(DirectedPositionable &player_pos, DirectedPositionable object);
    bool _hasMoved(DirectedPositionable& first, DirectedPositionable& second);
};


#endif //SOUNDHANDLER_H
