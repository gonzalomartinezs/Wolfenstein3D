#ifndef TEXTURESET_H
#define TEXTURESET_H

#include <vector>
#include "Texture.h"

class TextureSet {
private:
    std::vector <Texture> textures;
    unsigned period;

public:
    // Crea un set de texturas listo para ser utilizado
    TextureSet(std::vector<std::string> paths, SDL_Renderer *renderer,
               SDL_Surface *surface, unsigned period);

    // Sobrecarga de operador []
    Texture& get(int i);

    // Retorna el tamaño del set
    size_t size();

    // Retorna el periodo del set
    unsigned getPeriod();

    // Libera los recursos utilizados por el set.
    ~TextureSet();
};


#endif //TEXTURESET_H
