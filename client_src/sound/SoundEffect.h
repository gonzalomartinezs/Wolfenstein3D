#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
private:
    Mix_Chunk* sfx;

public:
    // Crea una instancia del objeto lista para ser utilizada.
    SoundEffect(std::string path);

    // Reproduce el sfx cargado de acuerdo a la cantidad de loops indicados.
    // Con -1 el sfx se repite hasta la destruccion del objeto.
    void play(int loops = 0);

    // Modifica el volumen de reproduccion en funcion al float recibido.
    // Se toma 0 como volumen en off y 1 volumen al maximo.
    void setVolume(float relative_volume);;

    // Libera los recuros utilizados por el objeto.
    ~SoundEffect();
};

#endif //SOUNDEFFECT_H
