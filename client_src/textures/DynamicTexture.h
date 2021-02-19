#ifndef DYNAMICTEXTURE_H
#define DYNAMICTEXTURE_H

#include <vector>
#include "TextureSet.h"
#include "../../common_src/Timer.h"

class DynamicTexture {
private:
    TextureSet* textures;
    Timer timer;
    int period;
    int state;
    bool single_event; // indica si la textura se anima una unica vez o
                       // si es un movimiento coninuo.

public:
    // Pre: los paths de la textura se encuentran ordenados.
    // Crea una textura dinamica lista para ser utilizada.
    DynamicTexture(TextureSet *textures, bool single_event);

    // Actualiza el set de texturas.
    void updateSet(TextureSet* texture);

    // Retorna una referencia a la textura que se desea renderizar.
    Texture* getTexture(int state);

    // Libera los recursos utilizados por la textura dinamica.
    ~DynamicTexture();

};


#endif //DYNAMICTEXTURE_H
