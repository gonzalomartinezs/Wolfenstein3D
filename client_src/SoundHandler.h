#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include "sound/SoundsContainer.h"

class SoundHandler {
private:
    SoundsContainer& sounds;
    int last_ammo;

public:
    // Crea un handler de sonidos listo para ser utilizado.
    explicit SoundHandler(SoundsContainer& sounds);

    void startBackMusic();

    // Libera los recursos utilizados por el objeto.
    ~SoundHandler();
};


#endif //WOLFENSTEINCLIENT_SOUNDHANDLER_H
