#ifndef SOUNDSCONTAINER_H
#define SOUNDSCONTAINER_H
#include <unordered_map>
#include "Music.h"
#include "SoundEffect.h"
#include "SoundID.h"

class SoundsContainer {
private:
    std::unordered_map<SoundID, Music*> music;
    std::unordered_map<SoundID, SoundEffect*> sfx;
    
public:
    // Crea un contenedor de sonidos con todos los sonidos del juego cargados.
    SoundsContainer();

    // Retorna un puntero a la cancion estatica solicitada.
    Music* getMusic(SoundID id);

    // Retorna un puntero al sfx solicitado.
    SoundEffect* getSFX(SoundID id);

    // Libera los recursos utilizados por el contenedor.
    ~SoundsContainer();

private:
    void _loadMusic();
    void _loadSFX();
};

#endif //SOUNDSCONTAINER_H
