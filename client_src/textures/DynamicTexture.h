#ifndef DYNAMICTEXTURE_H
#define DYNAMICTEXTURE_H

#include <vector>
#include "Texture.h"
#include "../../common_src/Timer.h"

class DynamicTexture {
private:
    std::vector <Texture> textures;
    Timer timer;
    int period;
    int state;

public:
    // Pre: los paths de la textura se encuentran ordenados.
    // Crea una textura dinamica lista para ser utilizada.
    DynamicTexture(std::vector<std::string> paths, SDL_Renderer* renderer,
                   SDL_Surface* surface, int period);

    // Actualiza el periodo de renderizado de la textura.
    void updatePeriod(int new_period);

    // Retorna una referencia a la textura que se desea renderizar.
    Texture& getTexture(int state);

    // Libera los recursos utilizados por la textura dinamica.
    ~DynamicTexture();

};


#endif //DYNAMICTEXTURE_H
