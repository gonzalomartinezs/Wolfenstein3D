#ifndef MUSIC_H
#define MUSIC_H
#include <SDL2/SDL_mixer.h>
#include <string>

class Music {
private:
    Mix_Music* music;

public:
    // Crea una instancia del objeto lista para ser utilizada.
    Music(std::string path);

    // Reproduce la cancion cargada de acuero a la cantidad de loops indicados.
    // Con -1 la musica loopea hasta la destruccion del objeto.
    void play(int loops);

    // Pausa la reproduccion de la cancion.
    void pause();

    // Retoma la reproduccion de la cancion, siempre y cuando haya sido
    // pausada previamente.
    void resume();

    // Modifica el volumen de reproduccion en funcion al float recibido.
    // Se toma 0 como volumen en off y 1 volumen al maximo.
    void setVolume(float relative_volume);

    // Detiene la reproduccion de la cancion.
    void stop();

    // Libera los recuros utilizados por el objeto.
    ~Music();
};

#endif //MUSIC_H
