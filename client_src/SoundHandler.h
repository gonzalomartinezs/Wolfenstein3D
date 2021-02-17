#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <vector>
#include "sound/SoundsContainer.h"

class SoundHandler {
private:
    SoundsContainer& sounds;
    int last_ammo;

public:
    // Crea un handler de sonidos listo para ser utilizado.
    explicit SoundHandler(SoundsContainer& sounds);

    // Comienza la reproduccion de la musica de fondo del juego.
    void startBackMusic();

    void loadGameSfx(std::vector<int>& player_info);

    // Libera los recursos utilizados por el objeto.
    ~SoundHandler();
};


#endif //WOLFENSTEINCLIENT_SOUNDHANDLER_H
