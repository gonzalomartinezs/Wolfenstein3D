#ifndef TEXTURESCONTAINER_H
#define TEXTURESCONTAINER_H
#include <SDL2/SDL_render.h>
#include <unordered_map>
#include "TextureID.h"
#include "Texture.h"

class TexturesContainer {
private:
    std::unordered_map<TextureID, Texture*> textures;
    SDL_Renderer* renderer;

public:
    // Crea un contenedor de texturas con todas las texturas del juego cargadas
    explicit TexturesContainer(SDL_Renderer* renderer);

    // Retorna un puntero a la textura solicitada.
    Texture* get(TextureID id);

    // Libera los recursos utilizados por el contenedor.
    ~TexturesContainer();
};


#endif //TEXTURESCONTAINER_H
